//
//  Path.hpp
//  aaaa
//
//  Created by Gyusun Yeom on 2016. 12. 8..
//  Copyright © 2016년 Gyusun Yeom. All rights reserved.
//

#ifndef Path_hpp
#define Path_hpp

#include <list>
#include "point.hpp"
#include "shplib/shapefil.h"

class Node;
class World;

class Path {
public:
    Path(SHPObject *obj, World &world);
    
    std::list<Point> points;
    Node * point1;
    Node * point2;
};

#endif /* Path_hpp */
