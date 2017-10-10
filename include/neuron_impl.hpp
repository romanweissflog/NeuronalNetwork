#ifndef NEURON_IMPL_HPP_
#define NEURON_IMPL_HPP_

double Neuron::GetOuputValue() const
{
  return activation_function::Sigmoid(m_value);
}

InputNeuron::InputNeuron(NeuronConnections const &output)
  : m_outputs(output)
{

}

void InputNeuron::SetInputValue(double v)
{
  m_value = v;
}

HiddenNeuron::HiddenNeuron(NeuronConnections const &input, 
  NeuronConnections const &output)
  : m_inputs(input)
  , m_outputs(output)
{

}

void HiddenNeuron::SetInputValue(double v)
{
  m_inputs.emplace_back();
}

OutputNeuron::OutputNeuron(NeuronConnections const &input)
  : m_inputs(input)
{

}

void OutputNeuron::SetInputValue(double v)
{
  m_inputs.emplace_back();
}

#endif
