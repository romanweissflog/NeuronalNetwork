#include "functions.h"
#include <algorithm>

namespace transfer_function
{
  double LinearSum(std::vector<WeightedInput> const &input)
  {
    double sum{};
    for (auto &&i : input)
    {
      sum += i.weight * i.value;
    }
    return sum;
  }
}

namespace activation_function
{
  double Sigmoid(double x)
  {
    return 1.0 / (1 + std::exp(x));
  }

  double Identity(double x)
  {
    return x;
  }

  double ReLu(double x)
  {
    return std::max(0.0, x);
  }
}
