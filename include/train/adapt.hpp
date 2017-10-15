#ifndef ADAPT_HPP_
#define ADAPT_HPP_

#include "network/network.hpp"
#include "learn_data.hpp"

namespace train
{
  template<typename NetworkType, typename OutputType>
  struct Adapt
  {
  public:
    Adapt(network::Network<NetworkType> &network)
      : m_network(network)
    {}

    void operator()(LearnData<NetworkType, OutputType> const &data)
    {
      m_network.ForwardPass(data.input);
      m_network.BackwardPass(data.groundTruth);
    }

  private:
    network::Network<NetworkType> &m_network;
  };
}


#endif
