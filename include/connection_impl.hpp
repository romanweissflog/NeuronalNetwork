#ifndef CONNECTION_IMPL_HPP_
#define CONNECTION_IMPL_HPP_

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
    return constants::gen(constants::re);
  }
}

Connection::Connection()
  : m_weight(Initialize())
{

}

#endif
