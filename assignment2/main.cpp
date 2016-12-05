
#include <cstdint>
#include <memory>
#include <exception>
#include <stdexcept>

template<typename T>
class Stack
{
  class Node
  {
  private:
    std::unique_ptr<T[]> values = nullptr;
    std::unique_ptr<Node> prev = nullptr;
  public:
    Node() = delete;

    explicit Node(uint_fast32_t size)
      : values(new T[size])
    {
    }

    void setPrev(std::unique_ptr<Node> &prevNode)
    {
      std::swap(prev, prevNode);
    }

    T &operator[](uint_fast32_t index)
    {
      return values[index];
    }
  };

private:
  uint_fast32_t _count = 0;
  uint_fast32_t _size = 0;
  uint_fast16_t _size_unit = 2;
  uint_fast16_t _node_filled = 0;
  std::unique_ptr<Node> _lastNode = nullptr;

public:
  Stack()
  {
    extendSize();
  }

  void push(const T& value)
  {
    if (_size == _count)
    {
      extendSize();
    }

    (*_lastNode)[_node_filled] = value;
    ++_count;
    ++_node_filled;
  }

  T pop()
  {
    if (_size <= 0)
    {
      throw std::underflow_error("stack underflow");
    }

    return nullptr;
  }

  void extendSize()
  {
    _size_unit *= 2;
    std::unique_ptr<Node> newNode = new Node(_size_unit);
    if (_lastNode != nullptr)
    {
      newNode->setPrev(_lastNode);
    }
    _lastNode = newNode;
    _node_filled = 0;
  }

  uint_fast32_t size() const
  {
    return _size;
  }

  uint_fast32_t count() const
  {
    return _count;
  }
};

template<typename T>
class Heap
{
  
};

int main(int /* argc */, char * /* argv */[])
{

  return 0;
}