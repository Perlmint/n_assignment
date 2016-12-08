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
#include "shplib/shapefil.h"

class Node;

class Path {
public:
    class Point {
    public:
        Point(double _x, double _y) : x(_x), y(_y) {}
        double x;
        double y;
    };
    
    Path(SHPObject *obj);
    
    std::list<Point> points;
    Node * point1;
    Node * point2;
};

#endif /* Path_hpp */
