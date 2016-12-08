#pragma once
#include <vector>
#include <functional>

/**
 * std::vector based binary heap
 */
template<typename T>
class Heap
{
public:
  explicit Heap(const std::function<bool(const T&, const T&)> &cmp = std::less<T>()) noexcept
    : _comparator(cmp)
  {}

  void put(T val)
  {
    _data.push_back(val);
    int curIndex = _data.size() - 1;
    auto parentIndex = getParentIndex(curIndex);
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
    auto curIndex = 0;
    auto childIndex = getLeftChildIndex(curIndex);

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
    return ret;
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

  static int getParentIndex(int index)
  {
    if (index == 0)
    {
      return -1;
    }

    // make 1-based index
    ++index;
    auto ret = 1;
    while (ret < index)
    {
      ret = (ret << 1) + 1;
    }
    ret >>= 1;

    return (ret >> 1) + (index - ret + 1) / 2 - 1;
  }

  static int getLeftChildIndex(int index)
  {
    ++index;
    auto ret = 1;
    while(ret < index)
    {
      ret = (ret << 1) + 1;
    }
    return ret;
  }
};
