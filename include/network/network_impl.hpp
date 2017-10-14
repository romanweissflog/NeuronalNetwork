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

namespace network
{

  template<size_t Size, typename T>
  Network<Size, T>::Network(size_t indent)
    : Common(indent)
  {
    size_t neuronCount{};
    m_inputLayer = Layer<T>(2, NeuronType::TypeInput, neuronCount, m_indent + 2);
    neuronCount += 3;
    for (size_t i{}; i < Size; ++i)
    {
      m_hiddenLayer[i] = Layer<T>(2, NeuronType::TypeHidden, neuronCount, m_indent + 2);
      neuronCount += 3;
    }
    m_outputLayer = Layer<T>(2, NeuronType::TypeOutput, neuronCount, m_indent + 2);

    GenerateFullyConnected();
  }

  template<size_t Size, typename T>
  void Network<Size, T>::GenerateFullyConnected()
  {
    auto connect = [](Layer<T> &out, Layer<T> &in)
    {
      for (auto &oN : out)
      {
        for (auto &iN : in)
        {
          if (iN->GetType() != NeuronType::TypeBias)
          {
            oN->Connect(iN);
          }
        }
      }
    };
    if (Size == 0)
    {
      connect(m_inputLayer, m_outputLayer);
    }
    if (Size >= 1)
    {
      connect(m_inputLayer, m_hiddenLayer[0]);
      for (size_t k = 1; k < Size - 1; ++k)
      {
        connect(m_hiddenLayer[k - 1], m_hiddenLayer[k]);
      }
      connect(m_hiddenLayer[Size - 1], m_outputLayer);
    }
  }

  template<size_t Size, typename T>
  void Network<Size, T>::ForwardPass(Input const &input)
  {
    Reset();

    if (input.size() != m_inputLayer.GetSize() - 1) // -1 because of Bias
    {
      throw std::runtime_error("Bad input size");
    }
    for (size_t i{}; i < input.size(); ++i)
    {
      if (m_inputLayer.GetNeuron(i)->GetType() == NeuronType::TypeBias)
      {
        continue;
      }
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

    for (size_t i{}; i < m_outputLayer.GetSize(); ++i)
    {
      m_currentOutput.push_back(m_outputLayer.GetNeuron(i)->GetOuputValue());
    }
  }

  template<size_t Size, typename T>
  void Network<Size, T>::Reset()
  {
    m_inputLayer.Reset();
    m_currentOutput.clear();

    for (size_t i{}; i < Size; ++i)
    {
      m_hiddenLayer[i].Reset();
    }

    m_outputLayer.Reset();
  }

  template<size_t Size, typename T>
  void Network<Size, T>::BackwardPass(Output const &expected)
  {
    if (expected.size() != m_outputLayer.GetSize())
    {
      throw std::runtime_error("Bad size of expected output vector");
    }
    Delta delta;

    // get delta values for output layer
    size_t idx{};
    for (auto &&n : m_outputLayer)
    {
      delta.push_back(first_derivate::Sigmoid(n->GetInputValue()) *
        (expected[idx] - n->GetOuputValue()));
      idx++;
    }

    auto adaptWeights = [](Layer<T> &layer, Delta const &deltas)
    {
      for (size_t i{}; i < deltas.size(); ++i)
      {
        for (auto &&n : layer)
        {
          double delta = constants::backwardEps * deltas[i] * n->GetOuputValue();
          n->GetConnection(i).AdaptWeight(delta);
        }
      }
    };

    if (Size == 0)
    {
      adaptWeights(m_inputLayer, delta);
    }
    else
    {
      adaptWeights(m_hiddenLayer[Size - 1], delta);

      auto getDelta = [](Layer<T> const &layer, Delta const &nextDelta) -> Delta
      {
        Delta deltas;
        size_t nextSize = nextDelta.size();
        for (auto &&n : layer)
        {
          if (n->GetType() == NeuronType::TypeBias)
          {
            continue;
          }
          double sum = 0.0;
          for (size_t i{}; i < nextSize; ++i)
          {
            sum += nextDelta[i] * n->GetConnection(i).GetOldWeight();
          }
          double delta = first_derivate::Sigmoid(n->GetInputValue()) * sum;
          deltas.push_back(delta);
        }
        return deltas;
      };

      for (size_t i = Size - 1; i >= 1; --i)
      {
        delta = getDelta(m_hiddenLayer[i], delta);
        adaptWeights(m_hiddenLayer[i - 1], delta);
      }

      delta = getDelta(m_inputLayer, delta);
      adaptWeights(m_inputLayer, delta);
    }
  }

  template<size_t Size, typename T>
  typename Network<Size, T>::Output Network<Size, T>::GetOutput() const
  {
    return m_currentOutput;
  }

  template<size_t Size, typename T>
  std::ostream& Network<Size, T>::Print(std::ostream &os) const
  {
    Indent(os);
    os << "Network\n";
    os << m_inputLayer;
    for (size_t i{}; i < Size; ++i)
    {
      os << m_hiddenLayer[i];
    }
    os << m_outputLayer;
    return os;
  }

  template<size_t Size, typename T>
  NetworkWeights Network<Size, T>::GetWeights() const
  {
    NetworkWeights weights;
    weights.emplace_back(0, m_inputLayer.GetWeights());
    for (size_t i{}; i < Size; ++i)
    {
      weights.emplace_back(i + 1, m_hiddenLayer[i].GetWeights());
    }
    weights.emplace_back(Size + 1, m_outputLayer.GetWeights());
    return weights;
  }

  template<size_t Size, typename T>
  void Network<Size, T>::SetWeights(NetworkWeights const &weights)
  {
    if (weights.size() != Size + 2)
    {
      throw std::runtime_error("Bad input size for network weights");
    }
    m_inputLayer.SetWeights(weights[0].second);
    for (size_t i{}; i < Size; ++i)
    {
      m_hiddenLayer[i].SetWeights(weights[i + 1].second);
    }
    m_outputLayer.SetWeights(weights[Size + 1].second);
  }
}

#endif
