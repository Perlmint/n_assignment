#include <vector>
#include <algorithm>
#include <cassert>
#include <iostream>

using data_type = std::pair<int, int>;
const std::vector<data_type> original_data = {
  {1, 10}, {2, 9}, {3, 8}, {4, 7}, {5, 6} };
//  102      89      82      81      86

/**
 * desc by first
 */
bool comparator1(const data_type &l, const data_type &r)
{
  return l.first > r.first;
}

/**
 * desc by second
 */
bool comparator2(const data_type &l, const data_type &r)
{
  return l.second > r.second;
}

/**
 * first ^ 2 * 2 + second ^ 2
 */
int squareIndex(const data_type &v)
{
  return (v.first * v.first) * 2 + (v.second * v.second);
}

/**
 * asc by squareIndex
 */
bool comparator3(const data_type &l, const data_type &r)
{
  return squareIndex(l) < squareIndex(r);
}

std::ostream &operator<<(std::ostream &stream, const std::vector<data_type> &value)
{
  stream << "{";
  auto first = true;
  for (const auto &item : value)
  {
    if (!first)
    {
      stream << ",";
    }
    stream << "(" << item.first << ", " << item.second << ")";
    first = false;
  }
  return stream << "}";
}

int main(int /* argc */, char * /*argv*/ [])
{
  auto data = std::vector<data_type>(original_data.begin(), original_data.end());

  // test comparator1
  std::cout << "comparator 1" << std::endl << "  sorting..." << std::endl;
  std::sort(data.begin(), data.end(), comparator1);
  assert(data[0].first == 5);
  assert(data[1].first == 4);
  assert(data[2].first == 3);
  assert(data[3].first == 2);
  assert(data[4].first == 1);
  std::cout << data;

  // test comparator2
  std::cout << "comparator 2" << std::endl << "  sorting..." << std::endl;
  std::sort(data.begin(), data.end(), comparator2);
  assert(data[0].second == 10);
  assert(data[1].second == 9);
  assert(data[2].second == 8);
  assert(data[3].second == 7);
  assert(data[4].second == 6);
  std::cout << data;

  // test comparator3
  std::cout << "comparator 3" << std::endl << "  sorting..." << std::endl;
  std::sort(data.begin(), data.end(), comparator3);
  assert(data[0].second == 7);
  assert(data[1].second == 8);
  assert(data[2].second == 6);
  assert(data[3].second == 9);
  assert(data[4].second == 10);
  std::cout << data;

  // normal exit
  return 0;
}