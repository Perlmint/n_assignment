//
//  Path.cpp
//  aaaa
//
//  Created by Gyusun Yeom on 2016. 12. 8..
//  Copyright © 2016년 Gyusun Yeom. All rights reserved.
//

#include "Path.hpp"

Path::Path(SHPObject *obj)
{
    for (uint32_t i = 0; i < obj->nVertices; i++)
    {
        points.push_back(Point(obj->padfX[i], obj->padfY[i]));
    }
}
