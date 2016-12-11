#include "World.hpp"
#include <set>
#include <iostream>
#include <algorithm>
#include "Path.hpp"

World::World()
  : _minX(std::numeric_limits<double>::max())
  , _minY(std::numeric_limits<double>::max())
  , _maxX(std::numeric_limits<double>::min())
  , _maxY(std::numeric_limits<double>::min())
{}

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
    auto nodeId = atoi(nodeIdStr);
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
    auto beginNodeId = atoi(beginNodeIdStr);
    auto endNodeIdStr = DBFReadStringAttribute(dbfHandle, i, endNodeIndex);
    auto endNodeId = atoi(endNodeIdStr);
    auto linkIdStr = DBFReadStringAttribute(dbfHandle, i, linkIdIndex);
    auto linkId = atoi(linkIdStr);
    auto beginNode = GetNodeOrCreateDummy(beginNodeId);
    auto path = new Path(obj, *this, linkId, rank,
      beginNode,
      GetNodeOrCreateDummy(endNodeId));
    beginNode->linkedPaths.push_back(path);
    _paths.emplace(path->id(), path);
    SHPDestroyObject(obj);

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
  }

  DBFClose(dbfHandle);
  SHPClose(shpHandle);
}

Node *World::GetNodeOrCreateDummy(int id)
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