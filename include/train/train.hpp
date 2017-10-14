#ifndef TRAIN_HPP_
#define TRAIN_HPP_

#include "network/network.hpp"
#include "network/types.h"
#include "train_data.hpp"

template<size_t Size, typename T, typename U>
struct Train
{
public:
  NetworkWeights operator()(TrainData<T, U> const &data);

private:
  network::Network<Size, T> m_network;
};

#endif
