#ifndef NEURON_IMPL_HPP_
#define NEURON_IMPL_HPP_

#include "functions.h"

#include <string>

namespace
{
  std::string to_string(NeuronType type)
  {
    switch (type)
    {
    case NeuronType::TypeUndef: return "Undef"; 
    case NeuronType::TypeInput: return "Input";
    case NeuronType::TypeHidden: return "Hidden";
    case NeuronType::TypeOutput: return "Output";
    case NeuronType::TypeBias: return "Bias";
    default:
      throw std::runtime_error("Unknown Neuron Type");
    }
  }
}

template<typename T>
Neuron<T>::Neuron(size_t idx, NeuronType type)
  : m_idx(idx)
  , m_type(type)
  , m_signal(idx)
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
InputNeuron<T>::InputNeuron(size_t idx)
  : Neuron<T>(idx, NeuronType::TypeInput)
{}

template<typename T>
void InputNeuron<T>::SetInputValue(double weight, T v)
{
  m_input = weight * v;
  m_output = weight * v;
}

template<typename T>
void InputNeuron<T>::Reset()
{
  m_input = -1.0;
  m_output = 1.0;
}

template<typename T>
void InputNeuron<T>::Connect(std::shared_ptr<Neuron> const &other)
{
  m_signal.Connect(std::bind(&Neuron::SetInputValue, other, std::placeholders::_1, std::placeholders::_2));
}


template<typename T>
HiddenNeuron<T>::HiddenNeuron(size_t idx)
  : Neuron<T>(idx, NeuronType::TypeHidden)
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
void HiddenNeuron<T>::Connect(std::shared_ptr<Neuron> const &other)
{
  m_signal.Connect(std::bind(&Neuron::SetInputValue, other, std::placeholders::_1, std::placeholders::_2));
}


template<typename T>
OutputNeuron<T>::OutputNeuron(size_t idx)
  : Neuron<T>(idx, NeuronType::TypeOutput)
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
BiasNeuron<T>::BiasNeuron(size_t idx)
  : Neuron<T>(idx, NeuronType::TypeBias)
{
  m_input = 1.0;
  m_output = 1.0;
}

template<typename T>
void BiasNeuron<T>::Connect(std::shared_ptr<Neuron> const &other)
{
  m_signal.Connect(std::bind(&Neuron::SetInputValue, other, std::placeholders::_1, std::placeholders::_2));
}

#endif
