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
    while (parentIndex != -1)
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
    while (childIndex <= lastIndex)
    {
      auto largest = curIndex;
      if (_comparator(_data[childIndex], _data[largest]))
      {
        largest = childIndex;
      }
      if (childIndex < lastIndex && _comparator(_data[childIndex + 1], _data[largest]))
      {
        largest = childIndex + 1;
      }

      if (largest != curIndex)
      {
        std::swap(_data[curIndex], _data[largest]);
        curIndex = largest;
        childIndex = getLeftChildIndex(curIndex);
      }
      else
      {
        break;
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

  typename std::vector<T>::const_reverse_iterator rbegin() const
  {
    return _data.rbegin();
  }

  typename std::vector<T>::const_reverse_iterator rend() const
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
    return ((index + 1) >> 1) - 1;
  }

  static int getLeftChildIndex(int index)
  {
    return ((index + 1) << 1) - 1;
  }
};
