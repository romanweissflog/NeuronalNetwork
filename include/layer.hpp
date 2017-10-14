#ifndef LAYER_HPP_
#define LAYER_HPP_

#include "neuron.hpp"

#include <vector>
#include <memory>

template<typename T>
class Layer
{
  using type = std::shared_ptr<Neuron<T>>;
  using NeuronLayer = std::vector<type>;
  using const_iterator = typename NeuronLayer::const_iterator;

public:
  Layer();
  Layer(size_t nrNeurons, NeuronType const &type, size_t totalNrExistingNeurons);
  ~Layer() = default;
  std::shared_ptr<Neuron<T>> GetNeuron(size_t idx);
  NeuronType GetNeuronType(size_t idx) const;
  size_t GetSize() const;
  void Process();
  void operator()();
  void Reset();

  const_iterator begin() const;
  const_iterator end() const;

private:
  NeuronLayer m_neurons;
  NeuronType m_type;
};

#include "layer_impl.hpp"

#endif
