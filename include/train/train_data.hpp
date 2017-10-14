#ifndef TRAIN_DATA_HPP_
#define TRAIN_DATA_HPP_

#include <vector>

template<typename T, typename U>
struct TrainData
{
  std::vector<T> input;
  std::vector<T> groundTruth;
};

#endif
