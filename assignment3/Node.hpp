//
//  Node.hpp
//  aaaa
//
//  Created by Gyusun Yeom on 2016. 12. 8..
//  Copyright © 2016년 Gyusun Yeom. All rights reserved.
//

#ifndef Node_hpp
#define Node_hpp

#include "shplib/shapefil.h"

class Node {
public:
    Node(SHPObject *obj)
    : _x(obj->dfXMin)
    , _y(obj->dfYMax)
    {}
    
    double x() const { return _x; }
    double y() const { return _y; }
    
    bool operator==(const Node& other) const {
        return _x == other._x && _y == other._y;
    }
private:
    double _x = std::numeric_limits<double>::quiet_NaN();
    double _y = std::numeric_limits<double>::quiet_NaN();
};

namespace std
{
    template<> struct hash<Node>
    {
    public:
        size_t operator()(const Node& node) const {
            return std::hash<double>()(node.x()) * std::hash<double>()(node.y());
        }
    };
}

#endif /* Node_hpp */
