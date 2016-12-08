
#include <cstdint>
#include <memory>
#include <vector>
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
  
};

int main(int /* argc */, char * /* argv */[])
{

  return 0;
}