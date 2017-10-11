#ifndef LAYER_IMPL_HPP_
#define LAYER_IMPL_HPP_

Layer::Layer()
{

}

Layer::Layer(size_t nrNeurons, NeuronType const &type, size_t neuronNumber)
{
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

#endif
