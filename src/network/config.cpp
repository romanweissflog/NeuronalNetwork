#include "config.h"

#include <fstream>

Config ReadConfig(std::string const &path)
{
  std::ifstream f(path);
  f.close();
  return {};
}