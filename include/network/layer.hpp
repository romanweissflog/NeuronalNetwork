#ifndef LAYER_HPP_
#define LAYER_HPP_

#include "neuron.hpp"
#include "common_interface.hpp"
#include "config.h"

#include <vector>
#include <memory>

namespace network
{
  template<typename T>
  class Layer : Common
  {
    using type = std::shared_ptr<Neuron<T>>;
    using NeuronLayer = std::vector<type>;
    using const_iterator = typename NeuronLayer::const_iterator;

  public:
    Layer();
    Layer(LayerConfig const &config, size_t totalNrExistingNeurons, size_t indent);
    ~Layer() = default;
    std::shared_ptr<Neuron<T>> GetNeuron(size_t idx);
    NeuronType GetNeuronType(size_t idx) const;
    size_t GetSize() const;
    void Process();
    void operator()();
    void Reset();
    std::ostream& Print(std::ostream &os) const override;
    LayerWeights GetWeights() const;
    void SetWeights(LayerWeights const &weights);

    const_iterator begin() const;
    const_iterator end() const;

  private:
    bool m_hasBias;
    NeuronLayer m_neurons;
    NeuronType m_type;
  };
}
#include "layer_impl.hpp"

#endif
