#ifndef NEURON_IMPL_HPP_
#define NEURON_IMPL_HPP_

#include "functions.h"

#include <string>

namespace network
{
  template<typename T>
  Neuron<T>::Neuron(size_t idx, NeuronType type, size_t indent)
    : Common(indent)
    , m_idx(idx)
    , m_type(type)
    , m_signal(idx, indent + 2)
    , m_input(0.0)
    , m_output(1.0)
  {}

  template<typename T>
  T Neuron<T>::GetOuputValue() const
  {
    return m_output;
  }

  template<typename T>
  T Neuron<T>::GetInputValue() const
  {
    return m_input;
  }

  template<typename T>
  Connection& Neuron<T>::GetConnection(size_t idx)
  {
    return m_signal.GetConnection(idx);
  }

  template<typename T>
  std::string Neuron<T>::GetName() const
  {
    return to_string(m_type) + "_" + std::to_string(m_idx);
  }

  template<typename T>
  NeuronType Neuron<T>::GetType() const
  {
    return m_type;
  }

  template<typename T>
  size_t Neuron<T>::GetIndex() const
  {
    return m_idx;
  }

  template<typename T>
  size_t Neuron<T>::GetConnectionSize() const
  {
    return m_signal.GetConnectionSize();
  }

  template<typename T>
  void Neuron<T>::Connect(std::shared_ptr<Neuron> const &)
  {
    throw std::exception("Neuron<T>::Connect not implemented");
  }

  template<typename T>
  void Neuron<T>::operator()()
  {
    m_signal.Emit(m_output);
  }

  template<typename T>
  void Neuron<T>::SetInputValue(double, T)
  {
    throw std::exception("Neuron<T>::SetInputValue not implemented");
  }

  template<typename T>
  void Neuron<T>::Process()
  {
    throw std::exception("Neuron<T>::Process not implemented");
  }

  template<typename T>
  void Neuron<T>::Reset()
  {

  }

  template<typename T>
  std::ostream& Neuron<T>::Print(std::ostream &os) const
  {
    Indent(os);
    os << "Neuron " << GetName() << ": input: " << m_input << ", output: " << m_output << "\n";
    for (auto &&c : m_signal)
    {
      os << c.first;
    }
    return os;
  }


  template<typename T>
  InputNeuron<T>::InputNeuron(size_t idx, size_t indent)
    : Neuron<T>(idx, NeuronType::TypeInput, indent)
  {}

  template<typename T>
  void InputNeuron<T>::SetInputValue(double /*weight*/, T v)
  {
    m_setInput = v;
    m_input = v;
    m_output = v;
  }

  template<typename T>
  void InputNeuron<T>::Reset()
  {
    m_input = m_setInput;
    m_output = 1.0;
  }

  template<typename T>
  void InputNeuron<T>::Connect(std::shared_ptr<Neuron<T>> const &other)
  {
    m_signal.Connect(std::bind(&Neuron::SetInputValue, other, std::placeholders::_1, std::placeholders::_2));
  }


  template<typename T>
  HiddenNeuron<T>::HiddenNeuron(size_t idx, size_t indent)
    : Neuron<T>(idx, NeuronType::TypeHidden, indent)
  {}

  template<typename T>
  void HiddenNeuron<T>::SetInputValue(double weight, T v)
  {
    m_inputValues.emplace_back(WeightedInput{ weight, v });
  }

  template<typename T>
  void HiddenNeuron<T>::Process()
  {
    m_input = transfer_function::LinearSum(m_inputValues);
    m_output = activation_function::Identity(m_input);
  }

  template<typename T>
  void HiddenNeuron<T>::Reset()
  {
    m_inputValues.clear();
  }

  template<typename T>
  void HiddenNeuron<T>::Connect(std::shared_ptr<Neuron<T>> const &other)
  {
    m_signal.Connect(std::bind(&Neuron::SetInputValue, other, std::placeholders::_1, std::placeholders::_2));
  }


  template<typename T>
  OutputNeuron<T>::OutputNeuron(size_t idx, size_t indent)
    : Neuron<T>(idx, NeuronType::TypeOutput, indent)
  {}

  template<typename T>
  void OutputNeuron<T>::SetInputValue(double weight, T v)
  {
    m_inputValues.emplace_back(WeightedInput{ weight, v });
  }

  template<typename T>
  void OutputNeuron<T>::Process()
  {
    m_input = transfer_function::LinearSum(m_inputValues);
    m_output = activation_function::Identity(m_input);
  }

  template<typename T>
  void OutputNeuron<T>::Reset()
  {
    m_inputValues.clear();
  }


  template<typename T>
  BiasNeuron<T>::BiasNeuron(size_t idx, size_t indent)
    : Neuron<T>(idx, NeuronType::TypeBias, indent)
  {
    m_input = 1.0;
    m_output = 1.0;
  }

  template<typename T>
  void BiasNeuron<T>::Connect(std::shared_ptr<Neuron<T>> const &other)
  {
    m_signal.Connect(std::bind(&Neuron::SetInputValue, other, std::placeholders::_1, std::placeholders::_2));
  }

  template<typename T>
  NeuronWeights Neuron<T>::GetWeights() const
  {
    return m_signal.GetWeights();
  }

  template<typename T>
  void Neuron<T>::SetWeights(NeuronWeights const &weights)
  {
    m_signal.SetWeights(weights);
  }
}

#endif
