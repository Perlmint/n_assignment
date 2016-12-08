#pragma once

class Point {
public:
  Point(double _x, double _y) : x(_x), y(_y) {}
  double x;
  double y;

  bool operator==(const Point& other) const {
    return x == other.x && y == other.y;
  }
};

namespace std
{
  template<> struct hash<Point>
  {
  public:
    size_t operator()(const Point& p) const {
      return std::hash<double>()(p.x) * std::hash<double>()(p.y);
    }
  };
}
