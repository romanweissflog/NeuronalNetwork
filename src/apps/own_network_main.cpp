#include "network/network.hpp"

#include <iostream>
#include <exception>

int main()
{
  using namespace network;
  using DNetwork = Network<1, double>;
  try
  {
    // create check
    DNetwork network;
    std::cout << network << "\n";

    // forward pass check
    DNetwork::Input input{ 1.0, 1.0 };
    network.ForwardPass(input);
    std::cout << network << "\n";

    // backward pass check
    auto const output = network.GetOutput();
    network.BackwardPass(output);
    std::cout << network << "\n";

    // weight get and set check
    auto const weights = network.GetWeights();
    network.SetWeights(weights);
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