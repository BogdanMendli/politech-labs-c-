#ifndef BASE_TYPES_HPP
#define BASE_TYPES_HPP

#include <memory>

namespace maschenko
{
  struct point_t
  {
    double x, y;
  };

  struct rectangle_t
  {
    point_t pos;
    double width, height;
  };

  struct pair_t
  {
    size_t line, column;
  };
}

#endif // BASETYPES_HPP
