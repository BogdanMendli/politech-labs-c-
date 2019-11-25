#include "Shape.hpp"

Shape::Shape(double x, double y):
  x_(x),
  y_(y)
{}
bool Shape::isMoreLeft(const Shape *shape) const
{
  return (x_ < shape->x_);
}
bool Shape::isUpper(const Shape *shape) const
{
  return (y_ > shape->y_);
}
