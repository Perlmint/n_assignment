#pragma once
#include <functional>
#include "stack.hpp"
#include "heap.hpp"

template<typename T>
class Vector
{
public:
  explicit Vector(const std::function<bool(const T&, const T&)> &cmp = std::less<T>()) noexcept
    : _heap(cmp)
  {}

  void push_back(const T& val)
  {
    if (++_size <= 4)
    {
      _stack.push(val);
    }
    else
    {
      if (_size == 5)
      {
        _heap.clear();
        for (const auto &v : _stack)
        {
          _heap.put(v);
        }
      }
      _heap.put(val);
    }
  }

  T pop_back()
  {
    if (--_size < 4)
    {
      return _stack.pop();
    }
    else
    {
      if (_size == 4)
      {
        _stack.clear();
        for (const auto &val : reverse(_heap))
        {
          _stack.push(val);
        }
        return _stack.pop();
      }
      return _heap.extract();
    }
  }

  T at(size_t index) const
  {
    if (_size <= 4)
    {
      return _stack[index];
    }
    else
    {
      return _heap[index];
    }
  }


private:
  Stack<T> _stack;
  Heap<T> _heap;
  size_t _size = 0;
};
