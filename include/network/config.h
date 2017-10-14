#ifndef CONFIG_H_
#define CONFIG_H_

#include <vector>

struct Layer
{
  size_t nrNeurons;
  std::string neuronType;
  std::string transferFunction;
  std::string activationFunction;
};

struct Config
{
  std::string networkType;
  std::vector<Layer> layers;
};

Config ReadConfig(std::string const &path);

#endif
