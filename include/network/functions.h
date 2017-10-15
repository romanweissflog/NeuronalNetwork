#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include "types.h"
#include <vector>

namespace network
{
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

  namespace first_derivate
  {
    double Sigmoid(double);
    double Identity(double);
    double ReLu(double);
  }
}

#endif
