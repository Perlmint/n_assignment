#pragma once

#include <vector>
#include "point.hpp"
#include "shapefil.h"

class Node;
class World;

class Path {
public:
  Path(SHPObject *obj, World &world, int id, int rank, Node *begin, Node *end);

  double length() const { return _length; }
  const std::vector<PointD> &points() const { return _points; }
  int id() const { return _id; }
  int rank() const { return _rank; }
  const Node *begin() const { return _begin; }
  const Node *end() const { return _end; }
private:
  int _id;
  int _rank;
  std::vector<PointD> _points;
  Node *_begin, *_end;
  double _length;
};
