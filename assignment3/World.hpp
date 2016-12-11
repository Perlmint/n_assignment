#pragma once

#include <memory>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include "Node.hpp"
#include "Path.hpp"
#include "shapefil.h"

namespace std
{
  template<> struct hash<std::pair<int, int>>
  {
  public:
    size_t operator()(const std::pair<int, int>& p) const {
      return std::hash<int>()(p.first) * std::hash<int>()(p.second);
    }
  };
}

template<typename T>
class IteratorRange
{
public:
  using iterator_type = typename T::const_iterator;
  IteratorRange(iterator_type beginItr, iterator_type endItr)
    : _beginItr(beginItr)
    , _endItr(endItr)
  {}

  iterator_type begin()
  {
    return _beginItr;
  }

  iterator_type end()
  {
    return _endItr;
  }
private:
  iterator_type _beginItr;
  iterator_type _endItr;
};

template<typename T>
IteratorRange<T> make_iterator_range(
  typename IteratorRange<T>::iterator_type begin,
  typename IteratorRange<T>::iterator_type end)
{
  return IteratorRange<T>(begin, end);
}

class World {
public:
  World();
  World(World &&) noexcept;
  World(const std::string &nodeFilePath, const std::string &linkFilePath);

  World &operator=(World &&) noexcept;

  void loadNode(const std::string &filePath);
  void loadLink(const std::string &filePath);

  uint64_t getNodeCount() const
  {
    return _nodes.size();
  }
  Node *getNode(double x, double y);

  friend std::ostream &operator<<(std::ostream &, const World &);

  std::unordered_multimap<Point, Path*>::const_iterator getLinkedPaths(const Point &point);

  Point center() const
  {
    return Point((_maxX + _minX) / 2, (_maxY + _minY) / 2);
  }

  const static int chunkSize = 1000;

  IteratorRange<std::multimap<std::pair<int, int>, Node*>> NodesByChunk(int x, int y) const;

private:
  uint64_t loadDefaultInfo(SHPHandle handle);

  double _minX;
  double _minY;
  double _maxX;
  double _maxY;

  std::unordered_map<Point, std::unique_ptr<Node>> _nodes;
  std::unordered_multimap<Point, Path*> _pathLink;
  std::unordered_set<std::unique_ptr<Path>> _paths;

  // for render
  std::multimap<std::pair<int, int>, Path*> _pathByChunks;
  std::multimap<std::pair<int, int>, Node*> _nodeByChunks;
};
