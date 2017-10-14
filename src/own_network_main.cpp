#include "network.hpp"

#include <iostream>
#include <exception>

int main()
{
  try
  {
    Network<1> network;
    network.DisplayInformation();
    Input input{ 1.0, 1.0 };
    network.ForwardPass(input);
    auto const output = network.GetOutput();
    for (auto &&o : output)
    {
      std::cout << o << "\n";
    }
    network.BackwardPass(output);
  }
  catch (std::runtime_error e)
  {
    std::cout << e.what() << "\n";
    return -1;
  }
  catch (...)
  {
    std::cout << "unknown exception\n";
    return -1;
  }
  return 0;
}