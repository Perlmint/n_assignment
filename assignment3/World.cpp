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
  , _pathLink(std::move(other._pathLink))
  , _paths(std::move(other._paths))
  , _pathByChunks(std::move(other._pathByChunks))
  , _nodeByChunks(std::move(other._nodeByChunks))
{}

World::World(const std::string &nodeFilePath, const std::string &linkFilePath)
  : World()
{
  loadNode(nodeFilePath);
  loadLink(linkFilePath);
  for (const auto &node : _nodes)
  {
    auto chunkPos = ChunkForPoint(node.first.x, node.first.y);
    _nodeByChunks.insert(std::make_pair(chunkPos, node.second.get()));
  }

  std::set<PointI> chunks;
  for (const auto &path : _paths)
  {
    chunks.clear();
    for (const auto &point : path->points())
    {
      auto curPoint = ChunkForPoint(point.x, point.y);
      chunks.insert(curPoint);
    }
    for (const auto chunkPoint : chunks)
    {
      _pathByChunks.insert(std::make_pair(chunkPoint, path.get()));
    }
  }
}

World &World::operator=(World &&other) noexcept
{
  _minX = other._minX;
  _minY = other._minY;
  _maxX = other._maxX;
  _maxY = other._maxY;
  _nodes = std::move(other._nodes);
  _pathLink = std::move(other._pathLink);
  _paths = std::move(other._paths);
  _nodeByChunks = std::move(other._nodeByChunks);
  _pathByChunks = std::move(other._pathByChunks);
  return *this;
}

void World::loadNode(const std::string &filePath)
{
  auto shpHandle = SHPOpen(filePath.c_str(), "rb");

  auto entityCount = loadDefaultInfo(shpHandle);

  for (auto i = 0; i < entityCount; i++) {
    auto obj = SHPReadObject(shpHandle, i);
    auto node = new Node(obj);
    _nodes.emplace(node->point(), node);
    SHPDestroyObject(obj);
  }

  SHPClose(shpHandle);
}

void World::loadLink(const std::string &filePath)
{
  auto shpHandle = SHPOpen(filePath.c_str(), "rb");

  auto entityCount = loadDefaultInfo(shpHandle);

  for (auto i = 0; i < entityCount; i++) {
    auto obj = SHPReadObject(shpHandle, i);
    auto path = new Path(obj, *this);
    _paths.emplace(path);
    _pathLink.insert(std::make_pair(path->points().front(), path));
    _pathLink.insert(std::make_pair(path->points().back(), path));
    SHPDestroyObject(obj);
  }

  SHPClose(shpHandle);
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

Node *World::getNode(double x, double y)
{
  auto itr = _nodes.find(PointD(x, y));
  if (itr == _nodes.end())
  {
    return nullptr;
  }
  else
  {
    return itr->second.get();
  }
}

std::unordered_multimap<PointD, Path*>::const_iterator World::getLinkedPaths(const PointD &point)
{
  return _pathLink.find(point);
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