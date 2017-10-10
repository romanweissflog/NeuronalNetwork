#ifndef LAYER_HPP_
#define LAYER_HPP_

#include "neuron.hpp"

#include <vector>
#include <memory>

class Layer
{
  using NeuronLayer = std::vector<std::shared_ptr<Neuron>>;
public:
  Layer(size_t nrNeurons = 0, NeuronType const &type = NeuronType::TypeUndef);
  ~Layer() = default;
  std::shared_ptr<Neuron> const GetNeuron(size_t idx) const;
  size_t GetSize() const;

private:
  NeuronLayer m_neurons;
};

#include "layer_impl.hpp"

#endif
