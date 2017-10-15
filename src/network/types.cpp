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
      throw std::runtime_error("Unknown neuron type");
    }
  }

  std::string to_string(NetworkType type)
  {
    switch (type)
    {
    case NetworkType::TypeNumber: return "number";
    case NetworkType::TypeImage: return "Image";
    case NetworkType::TypePointCloud: return "PointCloud";
    default:
      throw std::runtime_error("Unknown network type");
    }
  }

  std::string to_string(TransferFunctionType type)
  {
    switch (type)
    {
    case TransferFunctionType::TypeSum: return "sum";
    default:
      throw std::runtime_error("Unknown transfer function type");
    }
  }

  std::string to_string(ActivationFunctionType type)
  {
    switch (type)
    {
    case ActivationFunctionType::TypeIdentity: return "identity";
    case ActivationFunctionType::TypeSigmoid: return "sigmoid";
    case ActivationFunctionType::TypeReLu: return "relu";
    default:
      throw std::runtime_error("Unknown activation function type");
    }
  }
}