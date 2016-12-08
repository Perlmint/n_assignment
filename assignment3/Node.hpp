#pragma once

#include "point.hpp"
#include "shplib/shapefil.h"

class Node {
public:
  explicit Node(SHPObject *obj)
    : _point(obj->dfXMin, obj->dfYMax)
  {}

  double x() const { return _point.x; }
  double y() const { return _point.y; }

  const Point &point() const { return _point; }
private:
  Point _point;
};
