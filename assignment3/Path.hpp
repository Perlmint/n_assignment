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
  int id() const { return _id; }
  int rank() const { return _rank; }
private:
  int _id;
  int _rank;
  std::vector<PointD> _points;
  double _length;
};
