#ifndef NEURON_HPP_
#define NEURON_HPP_

#include "signal.hpp"
#include "connection.h"
#include "types.h"

#include <vector>
#include <memory>

template<typename T>
class Neuron
{
public:
  Neuron(size_t idx = 0, NeuronType type = NeuronType::TypeUndef);
  virtual ~Neuron() = default;
  virtual T GetOuputValue() const;
  virtual T GetInputValue() const;
  virtual Connection& GetConnection(size_t idx);
  virtual size_t GetConnectionSize() const;
  std::string GetName() const;
  NeuronType GetType() const;
  virtual void Connect(std::shared_ptr<Neuron> const &other);
  virtual void operator()();
  virtual void SetInputValue(double weight, T v);
  virtual void Process();
  virtual void Reset();

protected:
  ConnectedSignal<T> m_signal;
  size_t m_idx;
  NeuronType m_type;
  T m_input;
  T m_output;
};


template<typename T>
class InputNeuron : public Neuron<T>
{
public:
  InputNeuron(size_t idx);
  void SetInputValue(double weight, T v) override;
  void Reset() override;
  void Connect(std::shared_ptr<Neuron> const &other) override;
};


template<typename T>
class HiddenNeuron : public Neuron<T>
{
public:
  HiddenNeuron(size_t idx);
  void SetInputValue(double weight, T v) override;
  void Process() override;
  void Reset() override;
  void Connect(std::shared_ptr<Neuron> const &other) override;

private:
  std::vector<WeightedInput> m_inputValues;
};


template<typename T>
class OutputNeuron : public Neuron<T>
{
public:
  OutputNeuron(size_t idx);
  void SetInputValue(double weight, T v) override;
  void Process() override;
  void Reset() override;

private:
  std::vector<WeightedInput> m_inputValues;
};


template<typename T>
class BiasNeuron : public Neuron<T>
{
public:
  BiasNeuron(size_t idx);
  void Connect(std::shared_ptr<Neuron> const &other) override;
};

#include "neuron_impl.hpp"

#endif
