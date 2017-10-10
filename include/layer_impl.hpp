#ifndef LAYER_IMPL_HPP_
#define LAYER_IMPL_HPP_

Layer::Layer(size_t nrNeurons, NeuronType const &type)
{
  for (size_t i{}; i < nrNeurons; ++i)
  {
    if (type == NeuronType::TypeInput)
    {
      m_neurons.push_back(std::make_shared<InputNeuron>());
    }
    else if (type == NeuronType::TypeHidden)
    {
      m_neurons.push_back(std::make_shared<HiddenNeuron>());
    }
    else if (type == NeuronType::TypeOutput)
    {
      m_neurons.push_back(std::make_shared<OutputNeuron>());
    }
    else
    {
      throw std::runtime_error("Bad Neuron Type");
    }
  }
}

std::shared_ptr<Neuron> const Layer::GetNeuron(size_t idx) const
{
  if (idx >= m_neurons.size())
  {
    throw std::runtime_error("Bad index in GetNeuron");
  }
  return m_neurons[idx];
}

size_t Layer::GetSize() const
{
  return m_neurons.size();
}

#endif
