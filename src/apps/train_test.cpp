#include "train/train.hpp"

#include <iostream>
#include <exception>

int main()
{
  using namespace network;
  using namespace train;
  std::string configPath = "C:\\Users\\roman\\Documents\\Projekte\\NeuronalNetwork\\config.json";
  Config config = GetConfig(configPath);
  Train<double, double> networkTrain(config);
  try
  {
    std::vector<double> inputFF{ 0.0, 0.0 };
    std::vector<double> inputTF{ 1.0, 0.0 };
    std::vector<double> inputFT{ 0.0, 1.0 };
    std::vector<double> inputTT{ 1.0, 1.0 };
    std::vector<double> expectedF{ 0.0 };
    std::vector<double> expectedT{ 1.0 };
    train::LearnSet<double, double> learnSet
    { 
      { inputFF, expectedF },
      { inputTF, expectedF },
      { inputFT, expectedF },
      { inputTT, expectedT },
      { inputFF, expectedF },
      { inputTF, expectedF },
      { inputFT, expectedF },
      { inputTT, expectedT },
    };

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