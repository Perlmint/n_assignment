#include <cstdint>
#include <memory>
#include <vector>
#include <functional>
#include <exception>
#include <stdexcept>

template<typename T>
class Stack
{
private:
    std::vector<T> _data;
public:
  Stack() {}

  void push(const T& value)
  {
    _data.push_back(value);
  }

  T pop()
  {
    if (_data.size() <= 0)
    {
      throw std::underflow_error("stack underflow");
    }

    return _data.at(_data.size() - 1);
  }
    
  uint_fast32_t size() const
  {
    return _data.size();
  }
};

template<typename T>
class Heap
{
public:
  Heap()
    : _comparator(std::less<T>())
  {}
  Heap(const std::function<bool(const T&, const T&)> &cmp)
    : _comparator(cmp)
  {}

  void put(T val)
  {
    _data.push_back(val);
    int curIndex = _data.size() - 1;
    int parentIndex = getParentIndex(curIndex);
    while(parentIndex != -1) {
      if (_comparator(_data[curIndex], _data[parentIndex])) {
        std::swap(_data[curIndex], _data[parentIndex]);
        curIndex = parentIndex;
        parentIndex = getParentIndex(curIndex);
      }
      else {
        break;
      }
    }
  }

private:
  std::vector<T> _data;
  std::function<bool(const T&, const T&)> _comparator;

  int getParentIndex(int index)
  {
    if (index == 0)
    {
      return -1;
    }

    // make 1-based index
    ++index;
    int ret = 1;
    while(ret < index) {
      ret = (ret << 1) + 1;
    }
    ret >>= 1;

    return (ret >> 1) + (index - ret + 1) / 2 - 1;
  }
};

int main(int /* argc */, char * /* argv */[])
{

  return 0;
}