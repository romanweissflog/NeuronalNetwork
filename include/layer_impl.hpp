#ifndef LAYER_IMPL_HPP_
#define LAYER_IMPL_HPP_

template<typename T>
Layer<T>::Layer()
{

}

template<typename T>
Layer<T>::Layer(size_t nrNeurons, NeuronType const &type, size_t neuronNumber, size_t indent)
  : Common(indent)
  , m_type(type)
{
  if (type == NeuronType::TypeInput || type == NeuronType::TypeHidden)
  {
    m_neurons.emplace_back(std::make_shared<BiasNeuron<T>>(neuronNumber, m_indent + 2));
    neuronNumber++;
  }
  for (size_t i{}; i < nrNeurons; ++i, ++neuronNumber)
  {
    if (type == NeuronType::TypeInput)
    {
      m_neurons.emplace_back(std::make_shared<InputNeuron<T>>(neuronNumber, m_indent + 2));
    }
    else if (type == NeuronType::TypeHidden)
    {
      m_neurons.emplace_back(std::make_shared<HiddenNeuron<T>>(neuronNumber, m_indent + 2));
    }
    else if (type == NeuronType::TypeOutput)
    {
      m_neurons.emplace_back(std::make_shared<OutputNeuron<T>>(neuronNumber, m_indent + 2));
    }
    else
    {
      throw std::runtime_error("Bad Neuron Type");
    }
  }
}

template<typename T>
std::shared_ptr<Neuron<T>> Layer<T>::GetNeuron(size_t idx)
{
  if (idx >= m_neurons.size())
  {
    throw std::runtime_error("Bad index in GetNeuron");
  }
  return m_neurons[idx];
}

template<typename T>
NeuronType Layer<T>::GetNeuronType(size_t idx) const
{
  if (idx >= m_neurons.size())
  {
    throw std::runtime_error("Bad index in GetNeuronType");
  }
  return m_neurons[idx]->GetType();
}

template<typename T>
size_t Layer<T>::GetSize() const
{
  return m_neurons.size();
}

template<typename T>
void Layer<T>::Process()
{
  for (auto &&n : m_neurons)
  {
    if (n->GetType() != NeuronType::TypeBias && n->GetType() != NeuronType::TypeInput)
    {
      n->Process();
    }
  }
}

template<typename T>
void Layer<T>::operator()()
{
  for (auto &&n : m_neurons)
  {
    (*n)();
  }
}

template<typename T>
void Layer<T>::Reset()
{
  for (auto &&n : m_neurons)
  {
    n->Reset();
  }
}

template<typename T>
typename Layer<T>::const_iterator Layer<T>::begin() const
{
  return std::begin(m_neurons);
}

template<typename T>
typename Layer<T>::const_iterator Layer<T>::end() const
{
  return std::end(m_neurons);
}

template<typename T>
std::ostream& Layer<T>::Print(std::ostream &os) const
{
  Indent(os);
  os << "Layertype " << to_string(m_type) << "\n";
  for (auto &&n : m_neurons)
  {
    os << *n;
  }
  return os;
}

#endif
