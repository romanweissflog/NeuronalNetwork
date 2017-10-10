#ifndef NETWORK_IMPL_HPP_
#define NETWORK_IMPL_HPP_

namespace
{

}

template<size_t Size>
Network<Size>::Network()
{
  m_inputLayer = Layer(2, NeuronType::TypeInput);
  m_outputLayer = Layer(2, NeuronType::TypeOutput);
  for (size_t i{}; i < Size; ++i)
  {
    m_hiddenLayer[i] = Layer(2, NeuronType::TypeHidden);
  }

  GenerateFullyConnected();
}

template<size_t Size>
void Network<Size>::GenerateFullyConnected()
{

}

template<size_t Size>
Output Network<Size>::operator()(Input const &input)
{
  if (input.size() != m_inputLayer.GetSize())
  {
    throw std::runtime_error("Bad input size");
  }
  for (size_t i{}; i < input.size(); ++i)
  {

  }

  Output output;
  for (auto &&o : m_outputLayer)
  {
    output.push_back(o.GetValue());
  }
  return output;
}

#endif
