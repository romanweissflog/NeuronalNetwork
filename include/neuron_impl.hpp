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
    default:
      throw std::runtime_error("Unknown Neuron Type");
    }
  }
}

Neuron::Neuron(size_t idx, NeuronType type)
  : m_idx(idx)
  , m_type(type)
  , m_signal(idx)
  , m_input(0.0)
  , m_output(1.0)
{}

double Neuron::GetOuputValue() const
{
  return m_output;
}

double Neuron::GetInputValue() const
{
  return m_input;
}

WeightedSignal Neuron::GetSignal(size_t idx)
{
  return m_signal;
}

std::string Neuron::GetName() const
{
  return to_string(m_type) + "_" + std::to_string(m_idx);
}

NeuronType Neuron::GetType() const
{
  return m_type;
}

void Neuron::Connect(std::shared_ptr<Neuron> const &)
{}

void Neuron::operator()()
{
  m_signal.Emit(m_output);
}

void Neuron::SetInputValue(double, double)
{

}

void Neuron::Process()
{

}

void Neuron::Reset()
{

}


InputNeuron::InputNeuron(size_t idx = 0)
  : Neuron(idx, NeuronType::TypeInput)
{}

void InputNeuron::SetInputValue(double weight, double v)
{
  m_input = weight * v;
  m_output = weight * v;
}

void InputNeuron::Reset()
{
  m_input = -1.0;
  m_output = 1.0;
}

void InputNeuron::Connect(std::shared_ptr<Neuron> const &other)
{
  m_signal.Connect(std::bind(&Neuron::SetInputValue, other, std::placeholders::_1, std::placeholders::_2));
}


HiddenNeuron::HiddenNeuron(size_t idx = 0)
  : Neuron(idx, NeuronType::TypeHidden)
{}

void HiddenNeuron::SetInputValue(double weight, double v)
{
  m_inputValues.emplace_back(WeightedInput{ weight, v });
}

void HiddenNeuron::Process()
{
  m_input = transfer_function::LinearSum(m_inputValues);
  m_output = activation_function::Identity(m_input);
}

void HiddenNeuron::Reset()
{
  m_inputValues.clear();
}

void HiddenNeuron::Connect(std::shared_ptr<Neuron> const &other)
{
  m_signal.Connect(std::bind(&Neuron::SetInputValue, other, std::placeholders::_1, std::placeholders::_2));
}


OutputNeuron::OutputNeuron(size_t idx = 0)
  : Neuron(idx, NeuronType::TypeOutput)
{}

void OutputNeuron::SetInputValue(double weight, double v)
{
  m_inputValues.emplace_back(WeightedInput{ weight, v });
}

void OutputNeuron::Process()
{
  m_input = transfer_function::LinearSum(m_inputValues);
  m_output = activation_function::Identity(m_input);
}

void OutputNeuron::Reset()
{
  m_inputValues.clear();
}

BiasNeuron::BiasNeuron(size_t idx)
  : Neuron(idx, NeuronType::TypeBias)
{
  m_output = 1.0;
}

#endif
