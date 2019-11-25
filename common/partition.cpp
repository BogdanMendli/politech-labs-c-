#include "partition.hpp"
#include <cmath>

bool maschenko::isOverlapping(p_shape shape1, p_shape shape2)
{
  if ((shape1 == nullptr) || (shape2 == nullptr))
  {
    return false;
  }

  bool overlapping_x = fabs(shape1->getFrameRect().pos.x - shape2->getFrameRect().pos.x)
      < ((shape1->getFrameRect().width / 2) + (shape2->getFrameRect().width / 2));
  bool overlapping_y = fabs(shape1->getFrameRect().pos.y - shape2->getFrameRect().pos.y)
      < ((shape1->getFrameRect().height / 2) + (shape2->getFrameRect().height / 2));

  return overlapping_x && overlapping_y;
}

maschenko::Matrix maschenko::part(const maschenko::CompositeShape &composite_shape)
{
  Matrix matrix;

  for (size_t i = 0; i < composite_shape.getShapeCount(); ++i)
  {
    size_t line = 0;
    size_t column = 0;

    for (size_t j = 0; j < matrix.getLines(); ++j)
    {
      for (size_t k = 0; k < matrix.getColumns(); ++k)
      {
        if (matrix[j][k] == nullptr)
        {
          column = k;
          line = j;
          break;
        }

        if (isOverlapping(composite_shape[i], matrix[j][k]))
        {
          column = 0;
          line = j + 1;
          break;
        }

        column = k + 1;
        line = j;
      }

      if (line == j)
      {
        break;
      }
    }

    matrix.add(composite_shape[i], {line, column});
  }

  return matrix;
}
