#pragma once
#include <functional>
#include "stack.hpp"
#include "heap.hpp"
#include "utils.hpp"

/**
 * Custom Vector using stack or heap
 */
template<typename T>
class Vector
{
public:
  explicit Vector(const std::function<bool(const T&, const T&)> &cmp = std::less<T>()) noexcept
    : _heap(cmp)
  {}

  Vector &operator=(const Vector &other)
  {
    _stack.clear();
    _heap.clear();
    _size = other._size;

    if (_size > 4)
    {
      _heap = other._heap;
    }
    _stack = other._stack;

    return *this;
  }

  Vector &operator=(Vector &&other) noexcept
  {
    _size = other._size;

    _heap = other._heap;
    _stack = other._stack;

    return *this;
  }

  Vector& operator=(std::initializer_list<T> ilist)
  {
    assign(ilist);

    return *this;
  }

  void assign(size_t count, const T& value)
  {
    _size = count;
    _stack.clear();
    _heap.clear();
    if (_size > 4)
    {
      for (auto i = 0; i < count; ++i)
      {
        _stack.push(value);
      }
    }
    else
    {
      for (auto i = 0; i < count; ++i)
      {
        _heap.push(value);
      }
    }
  }

  template< class InputIt >
  void assign(InputIt first, InputIt last)
  {
    for(; first != last; ++first)
    {
      push_back(*first);
    }
  }

  void assign(std::initializer_list<T> ilist)
  {
    _size = ilist.size();

    if (_size > 4)
    {
      for (const auto &val : ilist)
      {
        _stack.push(val);
      }
    }
    else
    {
      for (const auto &val : ilist)
      {
        _heap.push(val);
      }
    }
  }

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

  void pop_back()
  {
    if (--_size < 4)
    {
      _stack.pop();
    }
    else
    {
      _heap.extract();
      if (_size == 4)
      {
        
        _stack.clear();
        for (const auto &val : reverse(_heap))
        {
          _stack.push(val);
        }
        _stack.pop();
      }
    }
  }

  T &at(size_t index)
  {
    if (index > _size)
    {
      throw std::out_of_range("index is out of range");
    }

    if (_size <= 4)
    {
      return _stack[index];
    }
    else
    {
      return _heap[index];
    }
  }

  const T &at(size_t index) const
  {
    if (index > _size)
    {
      throw std::out_of_range("index is out of range");
    }

    if (_size <= 4)
    {
      return _stack[index];
    }
    else
    {
      return _heap[index];
    }
  }

  T operator[](size_t index) const
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

  T &operator[](size_t index)
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

  T front()
  {
    return at(0);
  }

  T last()
  {
    return at(size() - 1);
  }

  size_t size() const
  {
    return _size;
  }

  bool empty() const
  {
    return _size == 0;
  }

  void clear()
  {
    _size = 0;
    _stack.clear();
    // no need to clear heap. now
  }

  using iterator = typename std::vector<T>::iterator;
  using const_iterator = typename std::vector<T>::const_iterator;
  using const_reverse_iterator = typename std::vector<T>::const_reverse_iterator;

  const_iterator begin() const
  {
    if (_size > 4)
    {
      return _heap.begin();
    }

    return _heap.begin();
  }

  const_iterator end() const
  {
    if (_size > 4)
    {
      return _heap.end();
    }

    return _heap.end();
  }

  const_reverse_iterator rbegin() const
  {
    if (_size > 4)
    {
      return _heap.rbegin();
    }

    return _heap.rbegin();
  }

  const_reverse_iterator rend() const
  {
    if (_size > 4)
    {
      return _heap.rend();
    }

    return _heap.rend();
  }

private:
  Stack<T> _stack;
  Heap<T> _heap;
  size_t _size = 0;
};
