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

template<typename T>
IteratorRange<T> make_iterator_range(
  std::pair<typename IteratorRange<T>::iterator_type, typename IteratorRange<T>::iterator_type> rangePair)
{
  return IteratorRange<T>(rangePair.first, rangePair.second);
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

  std::unordered_multimap<PointD, Path*>::const_iterator getLinkedPaths(const PointD &point);

  PointD center() const
  {
    return PointD((_maxX + _minX) / 2, (_maxY + _minY) / 2);
  }

  const static int chunkSize = 1000;

  IteratorRange<std::multimap<PointI, Node*>> NodesByChunk(int x, int y) const;
  IteratorRange<std::multimap<PointI, Path*>> PathsByChunk(int x, int y) const;

private:
  uint64_t loadDefaultInfo(SHPHandle handle);

  double _minX;
  double _minY;
  double _maxX;
  double _maxY;

  std::unordered_map<PointD, std::unique_ptr<Node>> _nodes;
  std::unordered_multimap<PointD, Path*> _pathLink;
  std::unordered_set<std::unique_ptr<Path>> _paths;

  // for render
  std::multimap<PointI, Path*> _pathByChunks;
  std::multimap<PointI, Node*> _nodeByChunks;
  static PointI ChunkForPoint(double x, double y);
};
