//
//  World.cpp
//  aaaa
//
//  Created by Gyusun Yeom on 2016. 12. 8..
//  Copyright © 2016년 Gyusun Yeom. All rights reserved.
//

#include "World.hpp"
#include <string>
#include <iostream>

World::World(const std::string &nodeFilePath, const std::string &linkFilePath)
{
    loadNode(nodeFilePath);
    loadLink(linkFilePath);
}

void World::loadNode(const std::string &filePath)
{
    auto shpHandle = SHPOpen(filePath.c_str(), "rb");
    
    auto entityCount = loadDefaultInfo(shpHandle);
    
    for (int32_t i = 0; i < entityCount; i++) {
        SHPObject *obj = SHPReadObject(shpHandle, i);
        _nodes.emplace(obj);
        SHPDestroyObject(obj);
    }
    
    SHPClose(shpHandle);
}

void World::loadLink(const std::string &filePath)
{
    auto shpHandle = SHPOpen(filePath.c_str(), "rb");
    
    auto entityCount = loadDefaultInfo(shpHandle);
    
    for (int32_t i = 0; i < entityCount; i++) {
        SHPObject *obj = SHPReadObject(shpHandle, i);
        //_nodes.push_back(std::move(Node(obj)));
        SHPDestroyObject(obj);
    }
    
    SHPClose(shpHandle);
}

uint64_t World::loadDefaultInfo(SHPHandle handle)
{
    int32_t entityCount = -1, shapeType = -1;
    double minimumBound[4], maximumBound[4];
    
    SHPGetInfo(handle, &entityCount, &shapeType, minimumBound, maximumBound);
    _minX = std::min(_minX, minimumBound[0]);
    _maxX = std::max(_maxX, maximumBound[0]);
    _minY = std::min(_minY, minimumBound[1]);
    _maxY = std::max(_maxY, maximumBound[1]);
    
    return entityCount;
}

std::ostream &operator<<(std::ostream &s, const World &w)
{
    return s << "[World" << std::endl
    << "  x: " << w._minX << " ~ " << w._maxX << std::endl
    << "  y: " << w._minY << " ~ " << w._maxY << std::endl
    << "  nodes count: " << w._nodes.size() << std::endl
    << "]";
}
