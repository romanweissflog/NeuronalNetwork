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

Connection::Connection(double weight)
  : m_weight(weight)
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