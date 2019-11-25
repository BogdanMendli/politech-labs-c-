#include "declarations.hpp"
#include <stdexcept>

sortOrder getSortOrder(const std::string &param)
{
  if (param == "ascending")
  {
    return sortOrder::ascending;
  }
  else if (param == "descending")
  {
    return sortOrder::descending;
  }
  else
  {
    throw std::invalid_argument("Incorrect parameter for sorting.");
  }
};
