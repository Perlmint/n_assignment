#pragma once
#include <cmath>

template<typename T>
class Point {
public:
  Point(T _x, T _y) : x(_x), y(_y) {}
  T x;
  T y;

  bool operator==(const Point& other) const {
    return x == other.x && y == other.y;
  }

  double distance(const Point& other) const
  {
    return std::sqrt(std::pow(x - other.x, 2) + std::pow(y - other.y, 2));
  }

  bool operator<(const Point& other) const {
    if (x != other.x)
    {
      return x < other.x;
    }
    return y < other.y;
  }

  bool operator>(const Point& other) const {
    return other < *this;
  }
};

using PointD = Point<double>;
using PointI = Point<int>;

namespace std
{
  template<typename T> struct hash<Point<T>>
  {
  public:
    size_t operator()(const Point<T>& p) const {
      return std::hash<T>()(p.x) * std::hash<T>()(p.y);
    }
  };
}
