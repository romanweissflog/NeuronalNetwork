#ifndef COMMON_INTERFACE_HPP_
#define COMMON_INTERFACE_HPP_

#include <ostream>

class Common
{
protected:
  Common(size_t indent = 0U)
    : m_indent(indent)
  {}

public:
  virtual std::ostream& Print(std::ostream &os) const = 0;

protected:
  void Indent(std::ostream &os) const
  {
    for (size_t i{}; i < m_indent; ++i)
    {
      os << " ";
    }
  }

protected:
  size_t m_indent;
};

template<class T>
auto operator<<(std::ostream& os, const T& t) -> decltype(t.Print(os), os)
{
  t.Print(os);
  return os;
}

#endif
