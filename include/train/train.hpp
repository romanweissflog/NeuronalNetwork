#ifndef TRAIN_HPP_
#define TRAIN_HPP_

#include "network/network.hpp"
#include "network/config.h"
#include "learn_data.hpp"
#include "eval.hpp"

namespace train
{
  template<typename NetworkType, typename OutputType>
  struct Train
  {
    using T = NetworkType;
    using U = OutputType;
  public:
    Train(network::Config const &config);
    network::NetworkWeights operator()(LearnSet<T, U> const &data, double percentageTrain);

  private:
    network::Network<T> m_network;
    Eval<U> m_eval;
  };
}

#include "train_impl.hpp"

#endif
