#pragma once

#include "point.hpp"
#include "shapefil.h"

class Node {
public:
  explicit Node(SHPObject *obj)
    : _point(obj->dfXMin, obj->dfYMax)
    , _id(obj->nShapeId)
  {}

  int id() const { return _id; }
  double x() const { return _point.x; }
  double y() const { return _point.y; }

  const PointD &point() const { return _point; }
private:
  PointD _point;
  int _id;
};
