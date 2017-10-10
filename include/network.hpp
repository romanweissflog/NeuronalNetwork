#ifndef NETWORK_HPP_
#define NETWORK_HPP_

#include "layer.hpp"

#include <array>

using Input = std::vector<double>;
using Output = std::vector<double>;

template<size_t Size>
class Network
{
public:
  Network();
  ~Network() = default;
  Output operator()(Input const &input);

private:
  void GenerateFullyConnected();

private:
  Layer m_inputLayer;
  Layer m_outputLayer;
  std::array<Layer, Size> m_hiddenLayer;
};

#include "network_impl.hpp"

#endif
