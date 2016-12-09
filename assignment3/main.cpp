#include <iostream>
#include "World.hpp"


int main(int argc, const char * argv[]) {
    World world{"./data/MOCT_NODE.shp", "./data/MOCT_LINK.shp"};
    
    std::cout << world << std::endl;
    return 0;
}
