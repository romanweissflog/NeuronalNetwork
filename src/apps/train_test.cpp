#include "train/train.hpp"

#include <iostream>
#include <exception>

int main()
{
  using namespace network;
  train::Train<double, double> networkTrain(0U);
  try
  {
    std::vector<double> input{};
    std::vector<double> expected{};
    train::LearnSet<double, double> learnSet{ {input, expected} };
    auto const finalWeights = networkTrain(learnSet, 0.5);
    std::cout << "Layersize: " << finalWeights.size() << "\n";
    std::cout << "Inputlayer neuron size: " << finalWeights[0].second.size() << "\n";
    std::cout << "Inputlayer neuron 1 connection size: " << finalWeights[0].second[1].second.size() << "\n";
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