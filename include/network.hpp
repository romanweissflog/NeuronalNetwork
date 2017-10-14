#ifndef NETWORK_HPP_
#define NETWORK_HPP_

#include "layer.hpp"

#include <array>

using Input = std::vector<double>;
using Output = std::vector<double>;

template<size_t Size>
class Network
{
  using Delta = std::vector<double>;

public:
  Network();
  ~Network() = default;
  void ForwardPass(Input const &input);
  void BackwardPass(Output const &expected);
  Output GetOutput() const;
  void DisplayInformation() const;

private:
  void Reset();
  void GenerateFullyConnected();

private:
  Layer<double> m_inputLayer;
  Layer<double> m_outputLayer;
  std::array<Layer<double>, Size> m_hiddenLayer;
  Output m_currentOutput;
};

#include "network_impl.hpp"

#endif
