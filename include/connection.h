#ifndef CONNECTION_H_
#define CONNECTION_H_

#include "common_interface.hpp"

class Connection : Common
{
public:
  Connection(double weight = 0.0, size_t indent = 0.0);
  void AdaptWeight(double delta);
  double GetWeight() const;
  double GetOldWeight() const;
  std::ostream& Print(std::ostream& os) const override;

private:
  double m_weight;
  double m_oldWeight;
};

#endif
