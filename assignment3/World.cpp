#include "World.hpp"
#include <set>
#include <iostream>
#include <algorithm>
#include <queue>
#include "Path.hpp"

World::World()
  : _minX(std::numeric_limits<double>::max())
  , _minY(std::numeric_limits<double>::max())
  , _maxX(std::numeric_limits<double>::min())
  , _maxY(std::numeric_limits<double>::min())
{
}

World::World(World &&other) noexcept
  : _minX(other._minX)
  , _minY(other._minY)
  , _maxX(other._maxX)
  , _maxY(other._maxY)
  , _nodes(std::move(other._nodes))
  , _paths(std::move(other._paths))
  , _pathByChunks(std::move(other._pathByChunks))
  , _nodeByChunks(std::move(other._nodeByChunks))
{}

World::World(const std::string &nodeFilePath, const std::string &linkFilePath)
  : World()
{
  loadNode(nodeFilePath);
  loadLink(linkFilePath);
}

World::~World()
{
  _running = false;
  _cv.notify_all();
  for (auto &thread : _threads)
  {
    thread.join();
  }
}

World &World::operator=(World &&other) noexcept
{
  _minX = other._minX;
  _minY = other._minY;
  _maxX = other._maxX;
  _maxY = other._maxY;
  _nodes = std::move(other._nodes);
  _paths = std::move(other._paths);
  _nodeByChunks = std::move(other._nodeByChunks);
  _pathByChunks = std::move(other._pathByChunks);
  return *this;
}

void World::BeginFinders()
{
  _running = true;
  for (auto i = 0; i < 5; ++i)
  {
    _threads.push_back(std::thread([this]() { finder(); }));
  }
}


void World::loadNode(const std::string &filePath)
{
  auto dbfPath = filePath;
  dbfPath.replace(dbfPath.length() - 3, 3, "dbf");
  auto dbfHandle = DBFOpen(dbfPath.c_str(), "rb");
  auto shpHandle = SHPOpen(filePath.c_str(), "rb");

  auto nodeIdIndex = DBFGetFieldIndex(dbfHandle, "NODE_ID");
  auto entityCount = loadDefaultInfo(shpHandle);

  for (auto i = 0; i < entityCount; i++) {
    auto obj = SHPReadObject(shpHandle, i);
    auto nodeIdStr = DBFReadStringAttribute(dbfHandle, i, nodeIdIndex);
    auto nodeId = atoll(nodeIdStr);
    auto node = new Node(obj, nodeId);
    _nodes.emplace(node->id(), node);
    SHPDestroyObject(obj);
    auto chunkPos = ChunkForPoint(node->x(), node->y());
    _nodeByChunks.insert(std::make_pair(chunkPos, node));
  }

  SHPClose(shpHandle);
}

void World::loadLink(const std::string &filePath)
{
  auto dbfPath = filePath;
  dbfPath.replace(dbfPath.length() - 3, 3, "dbf");
  auto dbfHandle = DBFOpen(dbfPath.c_str(), "rb");
  auto shpHandle = SHPOpen(filePath.c_str(), "rb");

  auto linkIdIndex = DBFGetFieldIndex(dbfHandle, "LINK_ID");
  auto roadRankIndex = DBFGetFieldIndex(dbfHandle, "ROAD_RANK");
  auto beginNodeIndex = DBFGetFieldIndex(dbfHandle, "F_NODE");
  auto endNodeIndex = DBFGetFieldIndex(dbfHandle, "T_NODE");

  auto entityCount = loadDefaultInfo(shpHandle);

  std::set<PointI> chunks;
  for (auto i = 0; i < entityCount; i++) {
    auto obj = SHPReadObject(shpHandle, i);
    auto rankStr = DBFReadStringAttribute(dbfHandle, i, roadRankIndex);
    auto rank = atoi(rankStr);
    auto beginNodeIdStr = DBFReadStringAttribute(dbfHandle, i, beginNodeIndex);
    auto beginNodeId = atoll(beginNodeIdStr);
    auto endNodeIdStr = DBFReadStringAttribute(dbfHandle, i, endNodeIndex);
    auto endNodeId = atoll(endNodeIdStr);
    auto linkIdStr = DBFReadStringAttribute(dbfHandle, i, linkIdIndex);
    auto linkId = atoll(linkIdStr);
    auto beginNode = GetNodeOrCreateDummy(beginNodeId);
    auto path = new Path(obj, *this, linkId, rank,
      beginNode,
      GetNodeOrCreateDummy(endNodeId));
    beginNode->linkedPaths.push_back(path);
    _paths.emplace(path->id(), path);

    chunks.clear();
    for (const auto &point : path->points())
    {
      auto curPoint = ChunkForPoint(point.x, point.y);
      chunks.insert(curPoint);
    }
    for (const auto chunkPoint : chunks)
    {
      _pathByChunks.insert(std::make_pair(chunkPoint, path));
    }
    SHPDestroyObject(obj);
  }

  DBFClose(dbfHandle);
  SHPClose(shpHandle);
}

Node *World::GetNodeOrCreateDummy(uint64_t id)
{
  auto itr = _nodes.find(id);
  if (itr == _nodes.end()) {
    return _nodes.emplace(id, new Node{id}).first->second.get();
  }

  return itr->second.get();
}

uint64_t World::loadDefaultInfo(SHPHandle handle)
{
  auto entityCount = -1, shapeType = -1;
  double minimumBound[4], maximumBound[4];

  SHPGetInfo(handle, &entityCount, &shapeType, minimumBound, maximumBound);
  _minX = std::min(_minX, minimumBound[0]);
  _maxX = std::max(_maxX, maximumBound[0]);
  _minY = std::min(_minY, minimumBound[1]);
  _maxY = std::max(_maxY, maximumBound[1]);

  return entityCount;
}

std::ostream &operator<<(std::ostream &s, const World &w)
{
  return s << "[World" << std::endl
    << "  x: " << w._minX << " ~ " << w._maxX << std::endl
    << "  y: " << w._minY << " ~ " << w._maxY << std::endl
    << "  nodes count: " << w._nodes.size() << std::endl
    << "]";
}

IteratorRange<std::multimap<PointI, Node*>> World::NodesByChunk(int x, int y) const
{
  auto range = _nodeByChunks.equal_range(PointI{ x, y });
  return make_iterator_range<std::multimap<PointI, Node*>>(
    range.first,
    range.second);
}

IteratorRange<std::multimap<PointI, Path*>> World::PathsByChunk(int x, int y) const
{
  return make_iterator_range<std::multimap<PointI, Path*>>(_pathByChunks.equal_range(PointI{ x, y }));
}

PointI World::ChunkForPoint(double x, double y)
{
  return PointI{
    static_cast<int>(x / chunkSize),
    static_cast<int>(y / chunkSize) };
}

using FindNearInfo = std::pair<PointI, double>;

struct FindNearComparator
{
  bool operator()(const FindNearInfo &l, const FindNearInfo &r) const
  {
    return l.second > r.second;
  }
  static FindNearInfo FindNearInfo(const PointI &chunk, const PointD &point)
  {
    return std::make_pair(chunk, point.distance(World::ChunkCenter(chunk)));
  }
};

Node *World::FindNearNode(const PointD &point) const
{
  Node *node = nullptr;
  std::priority_queue<FindNearInfo, std::vector<FindNearInfo>, FindNearComparator> chunkQueue;
  auto beginChunk = ChunkForPoint(point.x, point.y);
  chunkQueue.push(FindNearComparator::FindNearInfo(beginChunk, point));
  chunkQueue.push(FindNearComparator::FindNearInfo(PointI{ beginChunk.x - 1, beginChunk.y }, point));
  chunkQueue.push(FindNearComparator::FindNearInfo(PointI{ beginChunk.x + 1, beginChunk.y }, point));
  chunkQueue.push(FindNearComparator::FindNearInfo(PointI{ beginChunk.x, beginChunk.y - 1 }, point));
  chunkQueue.push(FindNearComparator::FindNearInfo(PointI{ beginChunk.x, beginChunk.y + 1 }, point));
  while (!chunkQueue.empty())
  {
    auto chunk = chunkQueue.top();
    chunkQueue.pop();
    node = FindNearNodeInChunk(point, chunk.first);
    if (node != nullptr && node->point().distance(point) < chunkSize / 3)
    {
      break;
    }
  }

  return node;
}

Node *World::FindNearNodeInChunk(const PointD &point, const PointI &chunk) const
{
  auto distance = std::numeric_limits<double>::max();
  Node *nearNode = nullptr;

  for (const auto &node : NodesByChunk(chunk.x, chunk.y))
  {
    auto curDistance = node.second->point().distance(point);
    if (curDistance < distance)
    {
      distance = curDistance;
      nearNode = node.second;
    }
  }

  return nearNode;
}

PointD World::ChunkCenter(const PointI &chunk)
{
  return PointD{ (chunk.x + 0.5) * chunkSize, (chunk.y + 0.5) * chunkSize };
}

std::future<std::vector<Path*>> World::FindPath(Node *begin, Node *end)
{
  // for fast develop... remove later
  if (begin == nullptr || end == nullptr)
  {
    return{};
  }

  _queueMutex.lock();
  if (_promiseIsValid)
  {
    _findPathPromise.set_exception(std::make_exception_ptr(std::runtime_error("Stopped")));
  }
  _findPathPromise = std::promise<std::vector<Path*>>();
  _promiseIsValid = true;
  while (!_queue.empty())
  {
    _queue.pop();
  }
  _queue.push(World::Estimation{
    std::vector<Path*>(),
    begin,
    end,
    0,
    0
  });
  _queueMutex.unlock();
  _cv.notify_one();

  return _findPathPromise.get_future();
}

void World::finder()
{
  while (_running)
  {
    {
      std::unique_lock<std::mutex> lock(_cvMutex);
      _cv.wait(lock);
    }

    Estimation prev;
    {
      std::unique_lock<std::mutex> queueLock(_queueMutex);
      if (_queue.empty())
      {
        continue;
      }
      prev = _queue.top();
      _queue.pop();
    }

    for (const auto &path : prev.node->linkedPaths)
    {
      prev.paths.push_back(path);
      if (path->end() == prev.target)
      {
        if (_promiseIsValid)
        {
          _promiseIsValid = false;
          _findPathPromise.set_value(prev.paths);
          std::unique_lock<std::mutex> queueLock(_queueMutex);
          while (!_queue.empty())
          {
            _queue.pop();
          }
        }
        break;
      }

      auto estimated = prev.real + path->length() + path->end()->point().distance(prev.target->point());
      {
        std::unique_lock<std::mutex> queueLock(_queueMutex);
        _queue.emplace(
          prev.paths,
          path->end(),
          prev.target,
          estimated,
          prev.real + path->length()
        );
      }
      _cv.notify_one();

      prev.paths.pop_back();
    }
  }
}