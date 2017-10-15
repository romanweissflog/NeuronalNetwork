#ifndef CONNECTION_H_
#define CONNECTION_H_

#include "common_interface.hpp"

namespace network
{
  class Connection : Common
  {
  public:
    Connection(size_t indent = 0.0);
    void AdaptWeight(double delta);
    double GetWeight() const;
    void SetWeight(double weight);
    double GetOldWeight() const;
    std::ostream& Print(std::ostream& os) const override;

  private:
    double m_weight;
    double m_oldWeight;
  };
}

#endif
