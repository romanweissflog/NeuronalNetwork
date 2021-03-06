#ifndef NETWORK_IMPL_HPP_
#define NETWORK_IMPL_HPP_

#include "functions.h"

#include <vector>

namespace network
{
  template<typename T>
  Network<T>::Network(Config const &config, size_t indent)
    : Common(indent)
    , m_hiddenLayerSize(config.layers.size() - 2)
    , m_step(config.step)
  {
    // TBD: use search to get correct config for layers
    size_t neuronCount{};
    m_inputLayer = Layer<T>(config.layers[0], neuronCount, m_indent + 2);
    neuronCount += 3;
    for (size_t i{}; i < m_hiddenLayerSize; ++i)
    {
      m_hiddenLayer.push_back(Layer<T>(config.layers[i + 1], neuronCount, m_indent + 2));
      neuronCount += 3;
    }
    m_outputLayer = Layer<T>(config.layers[m_hiddenLayerSize + 1], neuronCount, m_indent + 2);

    GenerateFullyConnected();
  }

  template<typename T>
  void Network<T>::GenerateFullyConnected()
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
    if (m_hiddenLayerSize == 0)
    {
      connect(m_inputLayer, m_outputLayer);
    }
    if (m_hiddenLayerSize >= 1)
    {
      connect(m_inputLayer, m_hiddenLayer[0]);
      for (size_t k = 1; k < m_hiddenLayerSize - 1; ++k)
      {
        connect(m_hiddenLayer[k - 1], m_hiddenLayer[k]);
      }
      connect(m_hiddenLayer[m_hiddenLayerSize - 1], m_outputLayer);
    }
  }

  template<typename T>
  void Network<T>::ForwardPass(Input const &input)
  {
    Reset();

    if (input.size() != m_inputLayer.GetSize()) // -1 because of Bias
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

    for (size_t i{}; i < m_hiddenLayerSize; ++i)
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

  template<typename T>
  void Network<T>::Reset()
  {
    m_inputLayer.Reset();
    m_currentOutput.clear();

    for (size_t i{}; i < m_hiddenLayerSize; ++i)
    {
      m_hiddenLayer[i].Reset();
    }

    m_outputLayer.Reset();
  }

  template<typename T>
  void Network<T>::BackwardPass(Output const &expected)
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

    auto adaptWeights = [this](Layer<T> &layer, Delta const &deltas)
    {
      for (size_t i{}; i < deltas.size(); ++i)
      {
        for (auto &&n : layer)
        {
          double delta = m_step * deltas[i] * n->GetOuputValue();
          n->GetConnection(i).AdaptWeight(delta);
        }
      }
    };

    if (m_hiddenLayerSize == 0)
    {
      adaptWeights(m_inputLayer, delta);
    }
    else
    {
      adaptWeights(m_hiddenLayer[m_hiddenLayerSize - 1], delta);

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

      for (size_t i = m_hiddenLayerSize - 1; i >= 1; --i)
      {
        delta = getDelta(m_hiddenLayer[i], delta);
        adaptWeights(m_hiddenLayer[i - 1], delta);
      }

      delta = getDelta(m_inputLayer, delta);
      adaptWeights(m_inputLayer, delta);
    }
  }

  template<typename T>
  typename Network<T>::Output Network<T>::GetOutput() const
  {
    return m_currentOutput;
  }

  template<typename T>
  std::ostream& Network<T>::Print(std::ostream &os) const
  {
    Indent(os);
    os << "Network\n";
    os << m_inputLayer;
    for (size_t i{}; i < m_hiddenLayerSize; ++i)
    {
      os << m_hiddenLayer[i];
    }
    os << m_outputLayer;
    return os;
  }

  template<typename T>
  NetworkWeights Network<T>::GetWeights() const
  {
    NetworkWeights weights;
    weights.emplace_back(0, m_inputLayer.GetWeights());
    for (size_t i{}; i < m_hiddenLayerSize; ++i)
    {
      weights.emplace_back(i + 1, m_hiddenLayer[i].GetWeights());
    }
    weights.emplace_back(m_hiddenLayerSize + 1, m_outputLayer.GetWeights());
    return weights;
  }

  template<typename T>
  void Network<T>::SetWeights(NetworkWeights const &weights)
  {
    if (weights.size() != m_hiddenLayerSize + 2)
    {
      throw std::runtime_error("Bad input size for network weights");
    }
    m_inputLayer.SetWeights(weights[0].second);
    for (size_t i{}; i < m_hiddenLayerSize; ++i)
    {
      m_hiddenLayer[i].SetWeights(weights[i + 1].second);
    }
    m_outputLayer.SetWeights(weights[m_hiddenLayerSize + 1].second);
  }
}

#endif
