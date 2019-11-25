#ifndef ELEMENT_HPP
#define ELEMENT_HPP
#include <string>

struct element_t
{
  enum type_t
  {
    NUMBER, WORD, MARK, DASH, SPACE
  };

  std::string value;
  type_t type;
};

#endif
