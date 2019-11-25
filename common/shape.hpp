#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "base-types.hpp"

namespace maschenko
{
  class Shape
  {
  public:
    virtual ~Shape() = default;

    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void move(const point_t &center) = 0;
    virtual void scale(double coefficient) = 0;
    virtual void writeInfo() const = 0;
    virtual void rotate(double angle) = 0;
    virtual point_t getCenter() const = 0;

  };
}

#endif // SHAPE_HPP
