#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <functional>
#include <vector>

struct WeightedInput
{
  double weight;
  double value;
};

namespace transfer_function
{
  double LinearSum(std::vector<WeightedInput> const &);
}

namespace activation_function
{
  double Sigmoid(double);
  double Identity(double);
  double ReLu(double);
}

#endif
