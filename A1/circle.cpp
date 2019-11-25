#define _USE_MATH_DEFINES
#include "circle.hpp"
#include <cmath>
#include <iostream>

Circle::Circle(const point_t &center, double radius) :
  center_(center),
  radius_(radius)
{
  if (radius_ <= 0)
  {
    std::cerr << "Invalid radius of circle." << std::endl;
  }
}

double Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

rectangle_t Circle::getFrameRect() const
{
  return rectangle_t {
    center_,
    2 * radius_,
    2 * radius_
  };
}

void Circle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void Circle::move(const point_t &center)
{
  center_ = center;
}

void Circle::writeInfo() const
{
  rectangle_t rectangle = getFrameRect();
  std::cout << std::endl
            << "Circle with center: (" << center_.x
            << ";" << center_.y << ")" << std::endl
            << "radius = " << radius_ << std::endl
            << "Frame rectangle width = " << rectangle.width
            << ", height = " << rectangle.height << std::endl
            << "Area = " << getArea() << std::endl << std::endl;
}
