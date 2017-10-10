#ifndef NEURON_HPP_
#define NEURON_HPP_

#include "connection.hpp"
#include "functions.h"

#include <vector>

using NeuronConnections = std::vector<Connection>;

enum NeuronType
{
  TypeUndef,
  TypeInput,
  TypeHidden,
  TypeOutput
};

class Neuron
{
public:
  virtual ~Neuron() = default;
  virtual void SetInputValue(double v) = 0;
  double GetOuputValue() const;

protected:
  double m_value;
};

class InputNeuron : public Neuron
{
public:
  InputNeuron(NeuronConnections const &outputs = {});
  void SetInputValue(double v);

private:
  NeuronConnections m_outputs;
};

class HiddenNeuron : public Neuron
{
public:
  HiddenNeuron(NeuronConnections const &inputs = {}, NeuronConnections const &outputs = {});
  void SetInputValue(double v);

private:
  std::vector<WeightedInput> m_inputs;
  NeuronConnections m_inputs;
  NeuronConnections m_outputs;
};

class OutputNeuron : public Neuron
{
public:
  OutputNeuron(NeuronConnections const &inputs = {}); 
  void SetInputValue(double v);

private:
  std::vector<WeightedInput> m_inputs;
  NeuronConnections m_inputs;
};

#include "neuron_impl.hpp"

#endif
