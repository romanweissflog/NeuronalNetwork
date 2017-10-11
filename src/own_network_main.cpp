#include "network.hpp"

#include <iostream>
#include <exception>

int main()
{
  try
  {
    Network<1> network;
    Input input{ 1.0, 1.0 };
    auto output = network(input);
    for (auto &&o : output)
    {
      std::cout << o << "\n";
    }
  }
  catch (std::runtime_error e)
  {
    std::cout << e.what() << "\n";
    return -1;
  }
  catch (...)
  {
    return -1;
  }
  return 0;
}