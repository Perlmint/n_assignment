#include "World.hpp"
#include <iostream>
#include <algorithm>
#include "Path.hpp"

World::World(World &&other) noexcept
  : _minX(other._minX)
  , _minY(other._minY)
  , _maxX(other._maxX)
  , _maxY(other._maxY)
  , _nodes(std::move(other._nodes))
  , _pathLink(std::move(other._pathLink))
  , _paths(std::move(other._paths))
{}

World::World(const std::string &nodeFilePath, const std::string &linkFilePath)
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
  _pathLink = std::move(other._pathLink);
  _paths = std::move(other._paths);
    return *this;
}

void World::loadNode(const std::string &filePath)
{
    auto shpHandle = SHPOpen(filePath.c_str(), "rb");
    
    auto entityCount = loadDefaultInfo(shpHandle);
    
    for (int32_t i = 0; i < entityCount; i++) {
        SHPObject *obj = SHPReadObject(shpHandle, i);
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
    
    for (int32_t i = 0; i < entityCount; i++) {
        SHPObject *obj = SHPReadObject(shpHandle, i);
        auto path = new Path(obj, *this);
        _paths.emplace(path);
        _pathLink.insert(std::make_pair(path->points.front(), path));
        _pathLink.insert(std::make_pair(path->points.back(), path));
        SHPDestroyObject(obj);
    }

    SHPClose(shpHandle);
}

uint64_t World::loadDefaultInfo(SHPHandle handle)
{
    int32_t entityCount = -1, shapeType = -1;
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
  auto itr = _nodes.find(Point(x, y));
  if (itr == _nodes.end())
  {
    return nullptr;
  }
  else
  {
    return itr->second.get();
  }
}

std::unordered_multimap<Point, Path*>::const_iterator World::getLinkedPaths(const Point &point)
{
  return _pathLink.find(point);
}