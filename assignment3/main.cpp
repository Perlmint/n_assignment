#include <iostream>
#include <future>
#include "World.hpp"

std::future<World> loadData()
{
  return std::async(std::launch::async, []()
  {
    return World{ "./data/MOCT_NODE.shp" , "./data/MOCT_LINK.shp" };
  });
}

int main(int argc, const char * argv[]) {
  auto world = loadData();
  world.wait();

  std::cout << world.get() << std::endl;
  return 0;
}
