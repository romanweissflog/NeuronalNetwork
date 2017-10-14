#include "network.hpp"

#include <iostream>
#include <exception>

int main()
{
  using namespace network;
  using DNetwork = Network<1, double>;
  try
  {
    DNetwork network;
    std::cout << network << "\n";
    DNetwork::Input input{ 1.0, 1.0 };
    network.ForwardPass(input);
    std::cout << network << "\n";
    auto const output = network.GetOutput();
    network.BackwardPass(output);
    std::cout << network << "\n";
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