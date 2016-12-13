#pragma once

#include <memory>
#include <unordered_map>
#include <map>
#include "Node.hpp"
#include "Path.hpp"
#include "shapefil.h"
#include <thread>
#include <mutex>
#include <queue>
#include <future>
#include <set>

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
  ~World();

  World &operator=(World &&) noexcept;

  void loadNode(const std::string &filePath);
  void loadLink(const std::string &filePath);

  uint64_t getNodeCount() const
  {
    return _nodes.size();
  }

  friend std::ostream &operator<<(std::ostream &, const World &);

  PointD center() const
  {
    return PointD((_maxX + _minX) / 2, (_maxY + _minY) / 2);
  }

  const static int chunkSize = 1000;

  IteratorRange<std::multimap<PointI, Node*>> NodesByChunk(int x, int y) const;
  IteratorRange<std::multimap<PointI, Path*>> PathsByChunk(int x, int y) const;

  Node *FindNearNode(const PointD &point) const;
  static PointD ChunkCenter(const PointI &chunk);
  std::future<std::vector<const Path*>> FindPath(Node *begin, Node *end);
  void BeginFinders();

private:
  uint64_t loadDefaultInfo(SHPHandle handle);

  double _minX;
  double _minY;
  double _maxX;
  double _maxY;

  std::unordered_map<uint64_t, std::unique_ptr<Node>> _nodes;
  std::unordered_map<uint64_t, std::unique_ptr<Path>> _paths;

  // for render
  std::multimap<PointI, Path*> _pathByChunks;
  std::multimap<PointI, Node*> _nodeByChunks;
  static PointI ChunkForPoint(double x, double y);
  Node *GetNodeOrCreateDummy(uint64_t id);
  Node *FindNearNodeInChunk(const PointD &point, const PointI &chunk) const;

  struct Estimation
  {
    Estimation()
      : prev(nullptr), node(nullptr)
      , path(nullptr), estimated(std::numeric_limits<double>::infinity())
      , real(0)
    {
    }

    Estimation *prev;
    const Node *node;
    const Path *path;
    double estimated;
    double real;
  };

  struct EstimationComparator
  {
    bool operator()(const Estimation *l, const Estimation *r) const
    {
      return l->estimated > r->estimated;
    }
  };

  std::priority_queue<Estimation*, std::vector<Estimation*>, EstimationComparator> _queue;
  std::map<uint64_t, Estimation> _estimations;
  std::set<const Node *> _visited;
  std::vector<std::thread> _threads;
  const Node *_target = nullptr;
  std::condition_variable _cv;
  std::mutex _cvMutex;
  std::mutex _queueMutex;
  std::promise<std::vector<const Path *>> _findPathPromise;
  std::atomic_bool _promiseIsValid = false;
  std::atomic_uint8_t _waiting = 0;
  std::condition_variable _waitingCv;
  std::mutex _waitingCvMutex;
  bool _running = false;
  void finder();
};
