#pragma once

#include "point.hpp"
#include "shapefil.h"

class Path;

class Node {
public:
  // dummy node constructor
  explicit Node(uint64_t id)
    : _point(0, 0)
    , _id(id)
    , _dummy(true)
  {}
  explicit Node(SHPObject *obj, uint64_t id)
    : _point(obj->dfXMin, obj->dfYMax)
    , _id(id)
    , _dummy(false)
  {}

  uint64_t id() const { return _id; }
  double x() const { return _point.x; }
  double y() const { return _point.y; }
  bool isDummy() const { return _dummy; }

  const PointD &point() const { return _point; }
  std::vector<Path *> linkedPaths;
private:
  PointD _point;
  uint64_t _id;
  bool _dummy;
};
