#include "Path.hpp"
#include "World.hpp"

Path::Path(SHPObject *obj, World &world)
  : length(0)
{
  for (auto i = 0; i < obj->nVertices; i++)
  {
    Point newPoint{ obj->padfX[i], obj->padfY[i] };
    if (i > 0)
    {
      length += points.back().distance(newPoint);
    }
    points.push_back(newPoint);
  }
  const auto &first = points.front();
  const auto &last = points.back();
  point1 = world.getNode(first.x, first.y);
  point2 = world.getNode(last.x, last.y);
}
