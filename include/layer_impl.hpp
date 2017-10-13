#ifndef LAYER_IMPL_HPP_
#define LAYER_IMPL_HPP_

Layer::Layer()
{

}

Layer::Layer(size_t nrNeurons, NeuronType const &type, size_t neuronNumber)
  : m_type(type)
{
  if (type == NeuronType::TypeInput || type == NeuronType::TypeHidden)
  {
    m_neurons.emplace_back(std::make_shared<BiasNeuron>(neuronNumber));
    neuronNumber++;
  }
  for (size_t i{}; i < nrNeurons; ++i, ++neuronNumber)
  {
    if (type == NeuronType::TypeInput)
    {
      m_neurons.emplace_back(std::make_shared<InputNeuron>(neuronNumber));
    }
    else if (type == NeuronType::TypeHidden)
    {
      m_neurons.emplace_back(std::make_shared<HiddenNeuron>(neuronNumber));
    }
    else if (type == NeuronType::TypeOutput)
    {
      m_neurons.emplace_back(std::make_shared<OutputNeuron>(neuronNumber));
    }
    else
    {
      throw std::runtime_error("Bad Neuron Type");
    }
  }
}

std::shared_ptr<Neuron> Layer::GetNeuron(size_t idx)
{
  if (idx >= m_neurons.size())
  {
    throw std::runtime_error("Bad index in GetNeuron");
  }
  return m_neurons[idx];
}

NeuronType Layer::GetNeuronType(size_t idx) const
{
  if (idx >= m_neurons.size())
  {
    throw std::runtime_error("Bad index in GetNeuronType");
  }
  return m_neurons[idx]->GetType();
}

size_t Layer::GetSize() const
{
  return m_neurons.size();
}

void Layer::Process()
{
  for (auto &&n : m_neurons)
  {
    n->Process();
  }
}

void Layer::operator()()
{
  for (auto &&n : m_neurons)
  {
    (*n)();
  }
}

void Layer::Reset()
{
  for (auto &&n : m_neurons)
  {
    n->Reset();
  }
}

Layer::iterator Layer::begin()
{
  return std::begin(m_neurons);
}

Layer::iterator Layer::end()
{
  return std::end(m_neurons);
}

Layer::const_iterator Layer::cbegin() const
{
  return std::cbegin(m_neurons);
}

Layer::const_iterator Layer::cend() const
{
  return std::cend(m_neurons);
}

#endif
