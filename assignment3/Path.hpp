#pragma once

#include <vector>
#include "point.hpp"
#include "shapefil.h"

class Node;
class World;

class Path {
public:
    Path(SHPObject *obj, World &world);
    
    std::vector<PointD> points;
    Node * point1;
    Node * point2;
    double length;
};
