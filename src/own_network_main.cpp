#include "network.hpp"

#include <iostream>
#include <exception>

int main()
{
  try
  {
    Network<1> network;
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