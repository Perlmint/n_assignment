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
  Stack() noexcept {}

  void push(const T& value)
  {
    _data.push_back(value);
  }

  void clear()
  {
    _data.clear();
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

  typename std::vector<T>::const_iterator begin() const
  {
    return _data.begin();
  }

  typename std::vector<T>::const_iterator end() const
  {
    return _data.end();
  }

  typename std::vector<T>::const_iterator rbegin() const
  {
    return _data.rbegin();
  }

  typename std::vector<T>::const_iterator rend() const
  {
    return _data.rend();
  }

  T operator[](size_t index) const
  {
    return _data.at(index);
  }

  T &operator[](size_t index)
  {
    return _data[index];
  }
};

template<typename T>
class Heap
{
public:
  Heap(const std::function<bool(const T&, const T&)> &cmp = std::less<T>()) noexcept
    : _comparator(cmp)
  {}

  void put(T val)
  {
    _data.push_back(val);
    int curIndex = _data.size() - 1;
    int parentIndex = getParentIndex(curIndex);
    while(parentIndex != -1)
    {
      if (_comparator(_data[curIndex], _data[parentIndex]))
      {
        std::swap(_data[curIndex], _data[parentIndex]);
        curIndex = parentIndex;
        parentIndex = getParentIndex(curIndex);
      }
      else
      {
        break;
      }
    }
  }

  T extract()
  {
    T ret = _data[0];
    _data[0] = _data.at(_data.size() - 1);
    _data.pop_back();
    int curIndex = 0;
    int childIndex = getLeftChildIndex(curIndex);

    int lastIndex = _data.size() - 1;
    while(childIndex <= lastIndex)
    {
      if (_comparator(_data[childIndex], _data[curIndex]))
      {
        std::swap(_data[curIndex], _data[childIndex]);
        curIndex = childIndex;
        childIndex = getLeftChildIndex(childIndex);
      }
      else
      {
        if (childIndex % 2 == 0)
        {
          break;
        }
        else
        {
          ++childIndex;
        }
      }
    }
  }

  void clear()
  {
    _data.clear();
  }

  typename std::vector<T>::const_iterator begin() const
  {
    return _data.begin();
  }

  typename std::vector<T>::const_iterator end() const
  {
    return _data.end();
  }

  typename std::vector<T>::const_iterator rbegin() const
  {
    return _data.rbegin();
  }

  typename std::vector<T>::const_iterator rend() const
  {
    return _data.rend();
  }

  T operator[](size_t index) const
  {
    return _data.at(index);
  }

  T &operator[](size_t index)
  {
    return _data[index];
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
    while (ret < index)
    {
      ret = (ret << 1) + 1;
    }
    ret >>= 1;

    return (ret >> 1) + (index - ret + 1) / 2 - 1;
  }

  int getLeftChildIndex(int index)
  {
    ++index;
    int ret = 1;
    while(ret < index)
    {
      ret = (ret << 1) + 1;
    }
    return ret;
  }
};

int main(int /* argc */, char * /* argv */[])
{

  return 0;
}
