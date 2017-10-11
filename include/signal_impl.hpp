#ifndef SIGNAL_IMPL_HPP_
#define SIGNAL_IMPL_HPP_

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


WeightedSignal::WeightedSignal(size_t idx)
  : Signal(idx)
{
  m_weight = Initialize();
}

void WeightedSignal::Emit(double value)
{
  for (auto &&slot : m_slots)
  {
    slot(m_weight, value);
  }
}

#endif
