#define _USE_MATH_DEFINES

#include "circle.hpp"
#include <cmath>
#include <iostream>
#include <stdexcept>

maschenko::Circle::Circle(const point_t &center, double radius) :
  center_(center),
  radius_(radius)
{
  if (radius_ <= 0)
  {
    throw std::invalid_argument("Invalid radius of circle.");
  }
}

double maschenko::Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

maschenko::rectangle_t maschenko::Circle::getFrameRect() const
{
  return rectangle_t
  {
    center_,
    2 * radius_,
    2 * radius_
  };
}

void maschenko::Circle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void maschenko::Circle::move(const point_t &center)
{
  center_ = center;
}

void maschenko::Circle::scale(double coefficient)
{
  if (coefficient > 0)
  {
    radius_ *= coefficient;
  }
  else
  {
    throw std::invalid_argument("Invalid coefficient for circle");
  }
}

void maschenko::Circle::writeInfo() const
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

maschenko::point_t maschenko::Circle::getCenter() const
{
  return center_;
}

double maschenko::Circle::getRadius() const
{
  return radius_;
}

void maschenko::Circle::rotate(double)
{}
