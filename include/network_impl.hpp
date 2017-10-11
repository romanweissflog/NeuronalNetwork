#ifndef NETWORK_IMPL_HPP_
#define NETWORK_IMPL_HPP_

namespace
{

}

template<size_t Size>
Network<Size>::Network()
{
  size_t neuronCount{};
  m_inputLayer = Layer(2, NeuronType::TypeInput, neuronCount);  
  neuronCount += 2;
  for (size_t i{}; i < Size; ++i)
  {
    m_hiddenLayer[i] = Layer(2, NeuronType::TypeHidden, neuronCount);
    neuronCount += 2;
  }
  m_outputLayer = Layer(2, NeuronType::TypeOutput, neuronCount);

  GenerateFullyConnected();
}

template<size_t Size>
void Network<Size>::GenerateFullyConnected()
{
  if (Size == 0)
  {
    for (size_t i{}; i < m_inputLayer.GetSize(); ++i)
    {
      for (size_t j{}; j < m_outputLayer.GetSize(); ++j)
      {
        m_inputLayer.GetNeuron(i)->Connect(m_outputLayer.GetNeuron(j));
      }
    }
  }
  if (Size >= 1)
  {
    for (size_t i{}; i < m_inputLayer.GetSize(); ++i)
    {
      for (size_t j{}; j < m_hiddenLayer[0].GetSize(); ++j)
      {
        m_inputLayer.GetNeuron(i)->Connect(m_hiddenLayer[0].GetNeuron(j));
      }
    }

    for (size_t k = 1; k < Size - 1; ++k)
    {
      for (size_t i{}; i < m_hiddenLayer[k].GetSize(); ++i)
      {
        for (size_t j{}; j < m_hiddenLayer[k + 1].GetSize(); ++j)
        {
          m_hiddenLayer[k].GetNeuron(i)->Connect(m_hiddenLayer[k + 1].GetNeuron(j));
        }
      }
    }

    for (size_t i{}; i < m_hiddenLayer[Size - 1].GetSize(); ++i)
    {
      for (size_t j{}; j < m_outputLayer.GetSize(); ++j)
      {
        m_hiddenLayer[Size - 1].GetNeuron(i)->Connect(m_outputLayer.GetNeuron(j));
      }
    }
  }
}

template<size_t Size>
Output Network<Size>::operator()(Input const &input)
{
  Reset();

  if (input.size() != m_inputLayer.GetSize())
  {
    throw std::runtime_error("Bad input size");
  }
  for (size_t i{}; i < input.size(); ++i)
  {
    m_inputLayer.GetNeuron(i)->SetInputValue(1.0, input[i]);
  }
  m_inputLayer.Process();
  m_inputLayer();

  for (size_t i{}; i < Size; ++i)
  {
    m_hiddenLayer[i].Process();
    m_hiddenLayer[i]();
  }

  m_outputLayer.Process();

  Output output;
  for (size_t i{}; i < m_outputLayer.GetSize(); ++i)
  {
    output.push_back(m_outputLayer.GetNeuron(i)->GetOuputValue());
  }
  return output;
}

template<size_t Size>
void Network<Size>::Reset()
{
  m_inputLayer.Reset();

  for (size_t i{}; i < Size; ++i)
  {
    m_hiddenLayer[i].Reset();
  }

  m_outputLayer.Reset();
}

#endif
