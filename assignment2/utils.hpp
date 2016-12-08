#pragma once

template <typename T>
struct ReverseAdapter
{
    T& iterable;
};

namespace std {
  template <typename T>
  auto begin(ReverseAdapter<T> w)
  {
    return rbegin(w.iterable);
  }

  template <typename T>
  auto end(ReverseAdapter<T> w)
  {
    return rend(w.iterable);
  }
}

template <typename T>
ReverseAdapter<T> reverse(T&& iterable)
{
  return ReverseAdapter<T>{iterable};
}
