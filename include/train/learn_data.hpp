#ifndef LEARN_DATA_HPP_
#define LEARN_DATA_HPP_

#include <vector>

namespace train
{
  template<typename InputType, typename OutputType>
  struct LearnData
  {
    std::vector<InputType> input;
    std::vector<OutputType> groundTruth;
  };
}

#endif
