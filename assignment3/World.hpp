//
//  World.hpp
//  aaaa
//
//  Created by Gyusun Yeom on 2016. 12. 8..
//  Copyright © 2016년 Gyusun Yeom. All rights reserved.
//

#ifndef World_hpp
#define World_hpp

#include <vector>
#include <unordered_set>
#include "Node.hpp"
#include "shplib/shapefil.h"

class World {
public:
    World(const std::string &nodeFilePath, const std::string &linkFilePath);
    
    uint64_t getNodeCount() const
    {
        return _nodes.size();
    }
    
    friend std::ostream &operator<<(std::ostream &, const World &);
    
private:
    void loadNode(const std::string &filePath);
    void loadLink(const std::string &filePath);
    uint64_t loadDefaultInfo(SHPHandle handle);
    
    double _minX = std::numeric_limits<double>::max();
    double _minY = std::numeric_limits<double>::max();
    double _maxX = std::numeric_limits<double>::min();
    double _maxY = std::numeric_limits<double>::min();
    
    std::unordered_set<Node> _nodes;
};


#endif /* World_hpp */
