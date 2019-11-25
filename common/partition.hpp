#ifndef COMMON_PARTITION_HPP
#define COMMON_PARTITION_HPP

#include "matrix.hpp"
#include "composite-shape.hpp"

using p_shape = std::shared_ptr<maschenko::Shape>;

namespace maschenko
{
  bool isOverlapping(p_shape shape1, p_shape shape2);
  Matrix part(const CompositeShape &composite_shape);
}

#endif //COMMON_PARTITION_HPP
