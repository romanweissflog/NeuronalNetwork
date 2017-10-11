#ifndef LAYER_HPP_
#define LAYER_HPP_

#include "neuron.hpp"

#include <vector>
#include <memory>

class Layer
{
  using NeuronLayer = std::vector<std::shared_ptr<Neuron>>;
public:
  Layer();
  Layer(size_t nrNeurons, NeuronType const &type, size_t totalNrExistingNeurons);
  ~Layer() = default;
  std::shared_ptr<Neuron> GetNeuron(size_t idx);
  size_t GetSize() const;
  void Process();
  void operator()();
  void Reset();

private:
  NeuronLayer m_neurons;
};

#include "layer_impl.hpp"

#endif
