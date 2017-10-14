#include "connection.h"

#include <random>

namespace
{
  namespace constants
  {
    std::default_random_engine re;
    std::uniform_real_distribution<double> gen(0.0, 1.0);
  }

  double Initialize()
  {
    return 1.0;
    return constants::gen(constants::re);
  }
}

namespace network
{

  Connection::Connection(double weight, size_t indent)
    : Common(indent)
    , m_weight(weight)
    , m_oldWeight(weight)
  {

  }

  void Connection::AdaptWeight(double delta)
  {
    m_oldWeight = m_weight;
    m_weight = m_weight + delta;
  }

  double Connection::GetWeight() const
  {
    return m_weight;
  }

  double Connection::GetOldWeight() const
  {
    return m_oldWeight;
  }

  std::ostream& Connection::Print(std::ostream& os) const
  {
    Indent(os);
    os << "Connection: oldWeight: " << m_oldWeight << ", weight: " << m_weight << "\n";
    return os;
  }
}
