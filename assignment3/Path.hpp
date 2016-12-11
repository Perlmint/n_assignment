#pragma once

#include <vector>
#include "point.hpp"
#include "shapefil.h"

class Node;
class World;

class Path {
public:
  Path(SHPObject *obj, World &world);

  double length() const { return _length; }
  const std::vector<PointD> &points() const { return _points; }
private:
  std::vector<PointD> _points;
  double _length;
};
