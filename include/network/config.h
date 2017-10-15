#ifndef CONFIG_H_
#define CONFIG_H_

#include <vector>
#include "types.h"

namespace network
{
  // tbd: use boost::optional for some variables
  struct LayerConfig
  {
    size_t nrNeurons;
    bool withBias;
    NeuronType type;
    TransferFunctionType transferFunction;
    ActivationFunctionType activationFunction;
  };

  struct Config
  {
    NetworkType networkType;
    std::vector<LayerConfig> layers;
  };

  Config GetConfig(std::string const &path);
}

#endif
