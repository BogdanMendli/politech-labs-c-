#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

namespace maschenko
{
  class Rectangle : public Shape
  {
  public:
    Rectangle(const point_t &center, double width, double height);

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(double dx, double dy) override;
    void move(const point_t &center) override;
    void scale(double coefficient) override;
    void writeInfo() const override;
    void rotate(double angle) override;
    point_t getCenter() const override;

  private:

    point_t apex_[4];
  };
}

#endif // RECTANGLE_HPP
