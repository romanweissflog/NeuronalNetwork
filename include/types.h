#ifndef TYPES_H_
#define TYPES_H_

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

#endif
