#ifndef NETWORK_IMPL_HPP_
#define NETWORK_IMPL_HPP_

#include "functions.h"

#include <vector>

namespace
{
  namespace constants
  {
    double const backwardEps = 0.1;
  }
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
        if (m_outputLayer.GetNeuronType(j) != NeuronType::TypeBias)
        {
          m_inputLayer.GetNeuron(i)->Connect(m_outputLayer.GetNeuron(j));
        }
      }
    }
  }
  if (Size >= 1)
  {
    for (size_t i{}; i < m_inputLayer.GetSize(); ++i)
    {
      for (size_t j{}; j < m_hiddenLayer[0].GetSize(); ++j)
      {
        if (m_hiddenLayer[0].GetNeuronType(j) != NeuronType::TypeBias)
        {
          m_inputLayer.GetNeuron(i)->Connect(m_hiddenLayer[0].GetNeuron(j));
        }
      }
    }

    for (size_t k = 1; k < Size - 1; ++k)
    {
      for (size_t i{}; i < m_hiddenLayer[k].GetSize(); ++i)
      {
        for (size_t j{}; j < m_hiddenLayer[k + 1].GetSize(); ++j)
        {
          if (m_hiddenLayer[k + 1].GetNeuronType(j) != NeuronType::TypeBias)
          {
            m_hiddenLayer[k].GetNeuron(i)->Connect(m_hiddenLayer[k + 1].GetNeuron(j));
          }
        }
      }
    }

    for (size_t i{}; i < m_hiddenLayer[Size - 1].GetSize(); ++i)
    {
      for (size_t j{}; j < m_outputLayer.GetSize(); ++j)
      {
        if (m_outputLayer.GetNeuronType(j) != NeuronType::TypeBias)
        {
          m_hiddenLayer[Size - 1].GetNeuron(i)->Connect(m_outputLayer.GetNeuron(j));
        }
      }
    }
  }
}

template<size_t Size>
void Network<Size>::ForwardPass(Input const &input)
{
  Reset();

  if (input.size() != m_inputLayer.GetSize() - 1) // -1 because of Bias
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

template<size_t Size>
void Network<Size>::BackwardPass(Output const &expected)
{
  if (expected.size() != m_outputLayer.GetSize())
  {
    throw std::runtime_error("Bad size of expected output vector");
  }
  Delta deltaOutput;
  deltaOutput.reserve(m_outputLayer.GetSize());
  
  // get delta values for output layer
  size_t idx{};
  for (auto &&n : m_outputLayer)
  {
    deltaOutput[idx] = first_derivate::Sigmoid(n->GetInputValue()) *
      (expected[idx] - n->GetOuputValue());
    idx++;
  }
  
  auto adaptWeights = [](Layer &layer, std::vector<double> const &delta)
  {
    for (auto &&d: delta)
    {
      for (auto &&n : layer)
      {
        double delta = constants::backwardEps * d * n->GetOuputValue();
        n->GetSignal().AdaptWeight(delta);
      }
    }
  };

  if (Size == 0)
  {
    adaptWeights(m_inputLayer, deltaOutput);
  }
  else
  {
    adaptWeights(m_hiddenLayer[Size - 1], deltaOutput);

    auto getDelta = [](Layer const &layer, Delta const &nextDelta) -> Delta
    {
      size_t idx{};
      Delta delta;
      for (auto &&n : layer)
      {
        double sum = 0.0;
        delta[idx] = first_derivate::Sigmoid(neuron->GetInputValue()) *
          (expected[idx] - neuron->GetOuputValue());
        idx++;
      }
      return delta;
    }

    for (auto &&iNeuron : m_inputLayer)
    {
      count = 0U;
      for (auto &&oNeuron : m_outputLayer)
      {
        delta = constants::backwardEps * deltaOutput[count] * iNeuron->GetOuputValue();
        iNeuron->GetSignal().AdaptWeight(delta);
      }
    }
  }
}

template<size_t Size>
Output Network<Size>::GetOutput() const
{
  return m_currentOutput;
}

#endif
