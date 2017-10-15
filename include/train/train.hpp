#ifndef TRAIN_HPP_
#define TRAIN_HPP_

#include "network/network.hpp"
#include "network/types.h"
#include "learn_data.hpp"
#include "eval.hpp"
#include "adapt.hpp"

namespace train
{
  template<typename NetworkType, typename OutputType>
  struct Train
  {
    using T = NetworkType;
    using U = OutputType;
  public:
    Train(size_t hiddenLayerSize = 0U);
    network::NetworkWeights operator()(LearnData<T, U> const &data, double percentageTrain);

  private:
    network::Network<T> m_network;
    Adapt<T, U> m_adapt;
    Eval<U> m_eval;
  };
}

#include "train_impl.hpp"

#endif
