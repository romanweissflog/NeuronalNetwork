#ifndef LAYER_HPP_
#define LAYER_HPP_

#include "neuron.hpp"

#include <vector>
#include <memory>

class Layer
{
  using type = std::shared_ptr<Neuron>;
  using NeuronLayer = std::vector<type>;
  using iterator = NeuronLayer::iterator;
  using const_iterator = NeuronLayer::const_iterator;
public:
  Layer();
  Layer(size_t nrNeurons, NeuronType const &type, size_t totalNrExistingNeurons);
  ~Layer() = default;
  std::shared_ptr<Neuron> GetNeuron(size_t idx);
  NeuronType GetNeuronType(size_t idx) const;
  size_t GetSize() const;
  void Process();
  void operator()();
  void Reset();

  iterator begin();
  iterator end();
  const_iterator cbegin() const;
  const_iterator cend() const;

private:
  NeuronLayer m_neurons;
  NeuronType m_type;
};

#include "layer_impl.hpp"

#endif
