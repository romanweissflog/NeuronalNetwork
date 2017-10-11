#ifndef NEURON_HPP_
#define NEURON_HPP_

#include "signal.hpp"
#include "types.h"

#include <vector>
#include <memory>

enum class NeuronType : uint8_t
{
  TypeUndef,
  TypeInput,
  TypeHidden,
  TypeOutput
};

class Neuron
{
public:
  Neuron(size_t idx = 0, NeuronType type = NeuronType::TypeUndef);
  virtual ~Neuron() = default;
  virtual void SetInputValue(double weight, double v) = 0;
  double GetOuputValue() const;
  virtual void Process();
  virtual void Reset() = 0;
  std::string GetName() const;
  virtual void Connect(std::shared_ptr<Neuron> const &other);
  virtual void operator()();

protected:
  WeightedSignal m_signal;
  size_t m_idx;
  NeuronType m_type;
  double m_value;
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

#include "neuron_impl.hpp"

#endif
