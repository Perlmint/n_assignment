#include "Path.hpp"
#include "World.hpp"

Path::Path(SHPObject *obj, World &world)
  : _length(0)
{
  for (auto i = 0; i < obj->nVertices; i++)
  {
    PointD newPoint{ obj->padfX[i], obj->padfY[i] };
    if (i > 0)
    {
      _length += _points.back().distance(newPoint);
    }
    _points.push_back(newPoint);
  }
}
