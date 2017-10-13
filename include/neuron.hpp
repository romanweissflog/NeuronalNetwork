#ifndef NEURON_HPP_
#define NEURON_HPP_

#include "signal.hpp"
#include "types.h"

#include <vector>
#include <memory>

class Neuron
{
public:
  Neuron(size_t idx = 0, NeuronType type = NeuronType::TypeUndef);
  virtual ~Neuron() = default;
  virtual double GetOuputValue() const;
  virtual double GetInputValue() const;
  virtual WeightedSignal GetSignal(size_t idx);
  std::string GetName() const;
  NeuronType GetType() const;
  virtual void Connect(std::shared_ptr<Neuron> const &other);
  virtual void operator()();
  virtual void SetInputValue(double weight, double v);
  virtual void Process();
  virtual void Reset();

protected:
  WeightedSignal m_signal;
  size_t m_idx;
  NeuronType m_type;
  double m_input;
  double m_output;
};

class InputNeuron : public Neuron
{
public:
  InputNeuron(size_t idx);
  void SetInputValue(double weight, double v) override;
  void Reset() override;
  void Connect(std::shared_ptr<Neuron> const &other) override;
};

class HiddenNeuron : public Neuron
{
public:
  HiddenNeuron(size_t idx);
  void SetInputValue(double weight, double v) override;
  void Process() override;
  void Reset() override;
  void Connect(std::shared_ptr<Neuron> const &other) override;

private:
  std::vector<WeightedInput> m_inputValues;
};

class OutputNeuron : public Neuron
{
public:
  OutputNeuron(size_t idx);
  void SetInputValue(double weight, double v) override;
  void Process() override;
  void Reset() override;

private:
  std::vector<WeightedInput> m_inputValues;
};

class BiasNeuron : public Neuron
{
public:
  BiasNeuron(size_t idx);
};

#include "neuron_impl.hpp"

#endif
