#include "network/types.h"

namespace network
{
  std::string to_string(NeuronType type)
  {
    switch (type)
    {
    case NeuronType::TypeUndef: return "Undef";
    case NeuronType::TypeInput: return "Input";
    case NeuronType::TypeHidden: return "Hidden";
    case NeuronType::TypeOutput: return "Output";
    case NeuronType::TypeBias: return "Bias";
    default:
      throw std::runtime_error("Unknown Neuron Type");
    }
  }
}