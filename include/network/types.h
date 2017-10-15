#ifndef TYPES_H_
#define TYPES_H_

#include <cstdint>
#include <string>
#include <vector>

namespace network
{
  // Common used usings
  using NeuronWeights = std::vector<double>;
  using LayerWeights = std::vector<std::pair<size_t, NeuronWeights>>;
  using NetworkWeights = std::vector<std::pair<size_t, LayerWeights>>;

  struct EmptyInput
  {};

  struct WeightedInput : EmptyInput
  {
    double weight;
    double value;
    WeightedInput(double weight_, double value_)
      : weight(weight_)
      , value(value_)
    {}
  };

  enum class NeuronType : uint8_t
  {
    TypeUndef,
    TypeInput,
    TypeHidden,
    TypeOutput,
    TypeBias
  };

  std::string to_string(NeuronType);
}
#endif
