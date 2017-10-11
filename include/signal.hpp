#ifndef SIGNAL_HPP_
#define SIGNAL_HPP_

#include "types.h"

#include <memory>
#include <vector>
#include <functional>

//template<typename... Args>
class Signal
{
protected:
  using Slot = std::function<void(double, double)>;

public:
  Signal(size_t idx = 0)
    : m_idx(idx)
  {}

  virtual ~Signal() = default;

  void Connect(Slot const &slot)
  {
    m_slots.push_back(slot);
  }

  virtual void Emit(double) = 0;

  size_t GetIdx() const
  {
    return m_idx;
  }

protected:
  std::vector<Slot> m_slots;
  size_t m_idx;
};

class WeightedSignal : public Signal
{
public:
  WeightedSignal(size_t idx = 0);
  void Emit(double val) override;

private:
  double m_weight;
};

#include "signal_impl.hpp"

#endif
