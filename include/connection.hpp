#ifndef CONNECTION_HPP_
#define CONNECTION_HPP_

class Connection
{
public:
  Connection();
  virtual ~Connection() = default;

private:
  double m_weight;
};

#include "connection_impl.hpp"

#endif
