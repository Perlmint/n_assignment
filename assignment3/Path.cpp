//
//  Path.cpp
//  aaaa
//
//  Created by Gyusun Yeom on 2016. 12. 8..
//  Copyright © 2016년 Gyusun Yeom. All rights reserved.
//

#include "Path.hpp"
#include "World.hpp"

Path::Path(SHPObject *obj, World &world)
{
  for (auto i = 0; i < obj->nVertices; i++)
  {
    points.push_back(Point(obj->padfX[i], obj->padfY[i]));
  }
  const auto &first = points.front();
  const auto &last = points.back();
  point1 = world.getNode(first.x, first.y);
  point2 = world.getNode(last.x, last.y);
}
