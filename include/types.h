#ifndef TYPES_H_
#define TYPES_H_

#include <cstdint>

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

#endif
