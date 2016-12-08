#pragma once
#include <vector>

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

  using const_iterator = typename std::vector<T>::const_iterator;

  const_iterator begin() const
  {
    return _data.begin();
  }

  const_iterator end() const
  {
    return _data.end();
  }

  const_iterator rbegin() const
  {
    return _data.rbegin();
  }

  const_iterator rend() const
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
