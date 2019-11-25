#include "rectangle.hpp"
#include <iostream>
#include <stdexcept>
#include <cmath>

maschenko::Rectangle::Rectangle(const point_t &center, double width, double height)
{
  if ((width <= 0) || (height <= 0))
  {
    throw std::invalid_argument("Invalid width of height of rectangle.");
  }
  apex_[0] = {center.x - width / 2, center.y + height / 2};
  apex_[1] = {center.x + width / 2, center.y + height / 2};
  apex_[2] = {center.x + width / 2, center.y - height / 2};
  apex_[3] = {center.x - width / 2, center.y - height / 2};
}

double maschenko::Rectangle::getArea() const
{
  double width_x = apex_[1].x - apex_[0].x;
  double width_y = apex_[1].y - apex_[0].y;
  double height_x = apex_[1].x - apex_[2].x;
  double height_y = apex_[1].y - apex_[2].y;

  return sqrt(width_x * width_x + width_y * width_y) * sqrt(height_x * height_x + height_y * height_y);
}

maschenko::rectangle_t maschenko::Rectangle::getFrameRect() const
{
  double left_frame = apex_[0].x;
  double right_frame = apex_[0].x;
  double top_frame = apex_[0].y;
  double bottom_frame = apex_[0].y;

  for (int i = 1; i < 4; ++i)
  {
    left_frame = std::min(left_frame, apex_[i].x);
    right_frame = std::max(right_frame, apex_[i].x);
    top_frame = std::max(top_frame, apex_[i].y);
    bottom_frame = std::min(bottom_frame, apex_[i].y);
  }
  return {{(right_frame + left_frame) / 2, (bottom_frame + top_frame) / 2},
    right_frame - left_frame, top_frame - bottom_frame};
}

void maschenko::Rectangle::move(double dx, double dy)
{
  for (int i = 0; i < 4; ++i)
  {
    apex_[i].x += dx;
    apex_[i].y += dy;
  }
}

void maschenko::Rectangle::move(const point_t &center)
{
  point_t this_center = getCenter();
  const double dx = center.x - this_center.x;
  const double dy = center.y - this_center.y;
  move(dx, dy);
}

void maschenko::Rectangle::scale(double coefficient)
{
  if (coefficient > 0)
  {
    point_t center = getCenter();
    double dx = coefficient * (apex_[1].x - center.x);
    double dy = coefficient * (apex_[1].y - center.y);

    apex_[0] = {center.x - dx, center.y + dy};
    apex_[1] = {center.x + dx, center.y + dy};
    apex_[2] = {center.x + dx, center.y - dy};
    apex_[3] = {center.x - dx, center.y - dy};
  }
  else
  {
    throw std::invalid_argument("Invalid coefficient for rectangle");
  }
}

void maschenko::Rectangle::writeInfo() const
{
  rectangle_t rectangle = getFrameRect();
  std::cout << std::endl << "Rectangle with center: (" << rectangle.pos.x
            << ";" << rectangle.pos.y << ")" << std::endl
            << "Frame rectangle width = " << rectangle.width
            << ", height = " << rectangle.height << std::endl
            << "Area = " << getArea() << std::endl << std::endl;
}

void maschenko::Rectangle::rotate(double angle)
{
  const double cos_angle = cos(angle);
  const double sin_angle = sin(angle);
  point_t center = getCenter();

  for (int i = 0; i < 4; ++i)
  {
    double point_x = center.x + (apex_[i].x - center.x) * cos_angle
        - (apex_[i].y - center.y) * sin_angle;
    double point_y = center.y + (apex_[i].x - center.x) * sin_angle
        + (apex_[i].y - center.y) * cos_angle;
    apex_[i] = {point_x, point_y};
  }
}

maschenko::point_t maschenko::Rectangle::getCenter() const
{
  return {(apex_[0].x + apex_[2].x) / 2, (apex_[0].y + apex_[2].y) / 2};
}
