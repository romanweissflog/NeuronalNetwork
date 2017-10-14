#ifndef NETWORK_HPP_
#define NETWORK_HPP_

#include "layer.hpp"
#include "common_interface.hpp"

#include <array>

namespace network
{
  template<typename T>
  class Network : Common
  {
    using Delta = std::vector<double>;

  public:
    using Input = std::vector<T>;
    using Output = std::vector<T>;

  public:
    Network(size_t nrHidden = 0, size_t ident = 0);
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
    size_t m_hiddenLayerSize;
    Layer<T> m_inputLayer;
    Layer<T> m_outputLayer;
    std::vector<Layer<T>> m_hiddenLayer;
    Output m_currentOutput;
  };
}

#include "network_impl.hpp"

#endif
