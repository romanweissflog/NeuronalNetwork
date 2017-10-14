#ifndef NETWORK_HPP_
#define NETWORK_HPP_

#include "layer.hpp"
#include "common_interface.hpp"

#include <array>

namespace network
{
  template<size_t Size, typename T>
  class Network : Common
  {
    using Delta = std::vector<double>;

  public:
    using Input = std::vector<T>;
    using Output = std::vector<T>;

  public:
    Network(size_t ident = 0);
    ~Network() = default;
    void ForwardPass(Input const &input);
    void BackwardPass(Output const &expected);
    Output GetOutput() const;
    std::ostream& Print(std::ostream &os) const override;
    NetworkWeights GetWeights() const;
    void SetWeights(NetworkWeights const &weights);

  private:
    void Reset();
    void GenerateFullyConnected();

  private:
    Layer<T> m_inputLayer;
    Layer<T> m_outputLayer;
    std::array<Layer<T>, Size> m_hiddenLayer;
    Output m_currentOutput;
  };
}

#include "network_impl.hpp"

#endif
