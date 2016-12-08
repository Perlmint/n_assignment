//
//  Node.hpp
//  aaaa
//
//  Created by Gyusun Yeom on 2016. 12. 8..
//  Copyright © 2016년 Gyusun Yeom. All rights reserved.
//

#ifndef Node_hpp
#define Node_hpp
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

#endif /* Node_hpp */
