#pragma once

#include <memory>
#include <unordered_set>
#include <unordered_map>
#include "Node.hpp"
#include "Path.hpp"
#include "shapefil.h"

class World {
public:
  World(const std::string &nodeFilePath, const std::string &linkFilePath);

  uint64_t getNodeCount() const
  {
    return _nodes.size();
  }
  Node *getNode(double x, double y);

  friend std::ostream &operator<<(std::ostream &, const World &);

  std::unordered_multimap<Point, Path*>::const_iterator getLinkedPaths(const Point &point);

private:
  void loadNode(const std::string &filePath);
  void loadLink(const std::string &filePath);
  uint64_t loadDefaultInfo(SHPHandle handle);

  double _minX = std::numeric_limits<double>::max();
  double _minY = std::numeric_limits<double>::max();
  double _maxX = std::numeric_limits<double>::min();
  double _maxY = std::numeric_limits<double>::min();

  std::unordered_map<Point, std::unique_ptr<Node>> _nodes;
  std::unordered_multimap<Point, Path*> _pathLink;
  std::unordered_set<std::unique_ptr<Path>> _paths;
};
