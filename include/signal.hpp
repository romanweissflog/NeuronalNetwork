#ifndef SIGNAL_HPP_
#define SIGNAL_HPP_

#include "types.h"
#include "connection.h"

#include <memory>
#include <vector>
#include <functional>

template<typename W, typename T>
class Signal
{
protected:
  using Slot = std::function<void(W, T)>;

public:
  Signal(size_t idx = 0)
    : m_idx(idx)
  {}

  virtual ~Signal() = default;

  virtual void Connect(Slot const &slot) = 0;
  virtual void Emit(T const &v) = 0;

  size_t GetIdx() const
  {
    return m_idx;
  }

protected:
  size_t m_idx;

private:
  std::vector<Slot> m_slots;
};


template<typename T>
class ConnectedSignal : public Signal<double, T>
{
  using ConnectedSlot = std::vector<std::pair<Connection, Slot>>;
public:
  ConnectedSignal(size_t idx)
    : Signal(idx)
  {}

  virtual void Connect(Slot const &slot)
  {
    Connection conn(1.0);
    m_slots.emplace_back(conn, slot);
  }

  virtual void Emit(T const &v)
  {
    for (auto &&s : m_slots)
    {
      s.second(s.first.GetWeight(), v);
    }
  }

  virtual size_t GetConnectionSize() const
  {
    return m_slots.size();
  }

  Connection& GetConnection(size_t idx)
  {
    if (idx >= m_slots.size())
    {
      throw std::runtime_error("Bad index for connection");
    }
    return m_slots[idx].first;
  }

private:
  ConnectedSlot m_slots;
};

#endif
