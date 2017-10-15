#ifndef SIGNAL_HPP_
#define SIGNAL_HPP_

#include "types.h"
#include "connection.h"

#include <memory>
#include <vector>
#include <functional>

namespace network
{
  template<typename W, typename T>
  class Signal
  {
  protected:
    using Slot = std::function<void(W, T)>;

  public:
    Signal(size_t idx = 0, size_t indent = 0)
      : m_idx(idx)
      , m_indent(indent)
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
    size_t m_indent;
  };


  template<typename T>
  class ConnectedSignal : public Signal<double, T>
  {
    using ConnectedSlot = std::vector<std::pair<Connection, Slot>>;
    using const_iterator = typename ConnectedSlot::const_iterator;
  public:
    ConnectedSignal(size_t idx, size_t indent)
      : Signal(idx, indent)
    {}

    virtual void Connect(Slot const &slot)
    {
      Connection conn(m_indent);
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

    const_iterator begin() const
    {
      return std::begin(m_slots);
    }

    const_iterator end() const
    {
      return std::end(m_slots);
    }

    NeuronWeights GetWeights() const
    {
      NeuronWeights weights;
      for (auto &&s : m_slots)
      {
        weights.push_back(s.first.GetWeight());
      }
      return weights;
    }

    void SetWeights(NeuronWeights const &weights)
    {
      if (weights.size() != m_slots.size())
      {
        throw std::runtime_error("Bad input size for connection weights");
      }
      size_t idx{};
      for (auto &&s : m_slots)
      {
        s.first.SetWeight(weights[idx]);
        idx++;
      }
    }

  private:
    ConnectedSlot m_slots;
  };
}

#endif
