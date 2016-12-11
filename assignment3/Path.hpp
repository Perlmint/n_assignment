#pragma once

#include <vector>
#include "point.hpp"
#include "shapefil.h"

class Node;
class World;

class Path {
public:
  Path(SHPObject *obj, World &world, uint64_t id, int rank, Node *begin, Node *end);

  double length() const { return _length; }
  const std::vector<PointD> &points() const { return _points; }
  uint64_t id() const { return _id; }
  int rank() const { return _rank; }
  const Node *begin() const { return _begin; }
  const Node *end() const { return _end; }
private:
  uint64_t _id;
  int _rank;
  std::vector<PointD> _points;
  Node *_begin, *_end;
  double _length;
};
