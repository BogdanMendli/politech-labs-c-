#include "composite-shape.hpp"
#include <iostream>
#include <stdexcept>
#include <cmath>

maschenko::CompositeShape::CompositeShape() :
  shape_count_(0)
{}

maschenko::CompositeShape::CompositeShape(const maschenko::CompositeShape &cs) :
  shape_count_(cs.shape_count_),
  shape_array_(std::make_unique<p_shape[]>(cs.shape_count_))
{
  for (size_t i = 0; i < shape_count_; ++i)
  {
    shape_array_[i] = cs.shape_array_[i];
  }
}

maschenko::CompositeShape::CompositeShape(maschenko::CompositeShape &&cs) :
  shape_count_(cs.shape_count_),
  shape_array_(std::move(cs.shape_array_))
{}

maschenko::CompositeShape& maschenko::CompositeShape::operator =(const CompositeShape& rhs)
{
  if (this != &rhs)
  {
    shape_count_ = rhs.shape_count_;
    std::unique_ptr<p_shape[]> new_shape_array(std::make_unique<p_shape[]>(rhs.shape_count_));
    for (size_t i = 0; i < shape_count_; i++)
    {
      new_shape_array[i] = rhs.shape_array_[i];
    }
    shape_array_.swap(new_shape_array);
  }

  return *this;
}

maschenko::CompositeShape& maschenko::CompositeShape::operator =(CompositeShape&& rhs)
{
  if (this != &rhs)
  {
    shape_count_ = rhs.shape_count_;
    shape_array_ = std::move(rhs.shape_array_);
  }

  return *this;
}

maschenko::CompositeShape::p_shape maschenko::CompositeShape::operator[](size_t index) const
{
  if (index >= shape_count_)
  {
    throw std::out_of_range("Index out of range");
  }
  return shape_array_[index];
}

double maschenko::CompositeShape::getArea() const
{
  double sum_shapes_area = 0;
  for (size_t i = 0; i < shape_count_; ++i)
  {
    sum_shapes_area += shape_array_[i]->getArea();
  }
  return sum_shapes_area;
}

maschenko::rectangle_t maschenko::CompositeShape::getFrameRect() const
{
  double max_x = shape_array_[0]->getFrameRect().pos.x;
  double min_x = shape_array_[0]->getFrameRect().pos.x;
  double max_y = shape_array_[0]->getFrameRect().pos.y;
  double min_y = shape_array_[0]->getFrameRect().pos.y;

  for (size_t i = 1; i < shape_count_; ++i)
  {
    rectangle_t temp_rect = shape_array_[i]->getFrameRect();

    double bottom_side = temp_rect.pos.y - temp_rect.height / 2;
    min_y = std::min(min_y, bottom_side);

    double top_side = temp_rect.pos.y + temp_rect.height / 2;
    max_y = std::max(max_y, top_side);

    double left_side = temp_rect.pos.x - temp_rect.width / 2;
    min_x = std::min(min_x, left_side);

    double right_side = temp_rect.pos.x + temp_rect.width / 2;
    max_x = std::max(max_x, right_side);
  }

  return rectangle_t{point_t{(max_x + min_x) / 2, (max_y + min_y) / 2}, max_x - min_x, max_y - min_y};
}

void maschenko::CompositeShape::move(double dx, double dy)
{
  for (size_t i = 0; i < shape_count_; ++i)
  {
    shape_array_[i]->move(dx, dy);
  }
}

void maschenko::CompositeShape::move(const maschenko::point_t &center)
{
  double dx = center.x - getFrameRect().pos.x;
  double dy = center.y - getFrameRect().pos.y;
  for (size_t i = 0; i < shape_count_; ++i)
  {
    shape_array_[i]->move(dx, dy);
  }
}

void maschenko::CompositeShape::scale(double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::invalid_argument("Invalid coefficient for CompositeShape");
  }

  const point_t pos = getFrameRect().pos;
  for (size_t i = 0; i < shape_count_; ++i)
  {
    double dx = shape_array_[i]->getFrameRect().pos.x - pos.x;
    double dy = shape_array_[i]->getFrameRect().pos.y - pos.y;
    shape_array_[i]->move((coefficient - 1) * dx, (coefficient - 1) * dy);
    shape_array_[i]->scale(coefficient);
  }
}

void maschenko::CompositeShape::writeInfo() const
{
  maschenko::rectangle_t temp_rect = getFrameRect();
  std::cout << std::endl
            << "Quantity shape in CompositeShape = " << shape_count_ << std::endl
            << "Area = " << getArea() << std::endl
            << "Frame rectangle width = " << temp_rect.width
            << ", height = " << temp_rect.height
            << ", and with center (" << temp_rect.pos.x << ";"
            << temp_rect.pos.y << ") " << std::endl << std::endl;
}

size_t maschenko::CompositeShape::getShapeCount() const
{
  return shape_count_;
}

void maschenko::CompositeShape::add(p_shape shape)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("shape equals null. It can't be");
  }

  std::unique_ptr<p_shape[]> new_shape_array(std::make_unique<p_shape[]>(shape_count_ + 1));

  for (size_t i = 0; i < shape_count_; ++i)
  {
    new_shape_array[i] = shape_array_[i];
  }
  new_shape_array[shape_count_] = shape;
  shape_count_++;
  shape_array_.swap(new_shape_array);
}

void maschenko::CompositeShape::remove(size_t index)
{
  if (index > shape_count_)
  {
    throw std::out_of_range("Index out of range");
  }

  std::unique_ptr<p_shape[]> new_shape_array(std::make_unique<p_shape[]>(shape_count_ - 1));

  for (size_t i = 0; i < index; ++i)
  {
    new_shape_array[i] = shape_array_[i];
  }

  shape_count_--;

  for (size_t i = index; i < shape_count_; ++i)
  {
    new_shape_array[i] = shape_array_[i + 1];
  }

  shape_array_.swap(new_shape_array);
}

void maschenko::CompositeShape::remove(p_shape shape)
{
  for (size_t i = 0; i < shape_count_; ++i)
  {
    if (shape == shape_array_[i])
    {
      remove(i);
      return;
    }
  }

  throw std::invalid_argument("This shape doesn't exist");
}

void maschenko::CompositeShape::rotate(double angle)
{
  const point_t center = getCenter();
  const double cos_angle = cos(angle);
  const double sin_angle = sin(angle);

  for (size_t i = 0; i < shape_count_; ++i)
  {
    const point_t other_center = shape_array_[i]->getCenter();
    double point_x = {center.x + (other_center.x - center.x) * cos_angle
        - (other_center.y - center.y) * sin_angle};
    double point_y = {center.y + (other_center.x - center.x) * sin_angle
        - (other_center.y - center.y) * cos_angle};

    shape_array_[i]->move({point_x, point_y});
    shape_array_[i]->rotate(angle);
  }
}

maschenko::point_t maschenko::CompositeShape::getCenter() const
{
  maschenko::rectangle_t frame_rect = shape_array_[0]->getFrameRect();
  double max_x = frame_rect.pos.x + frame_rect.width / 2;
  double min_x = frame_rect.pos.x - frame_rect.width / 2;
  double max_y = frame_rect.pos.y + frame_rect.height / 2;
  double min_y = frame_rect.pos.y - frame_rect.height / 2;

  for (size_t i = 1; i < shape_count_; ++i)
  {
    frame_rect = shape_array_[i]->getFrameRect();
    max_x = std::max(max_x, frame_rect.pos.x + frame_rect.width / 2);
    min_x = std::min(min_x, frame_rect.pos.x - frame_rect.width / 2);
    max_y = std::max(max_y, frame_rect.pos.y + frame_rect.height / 2);
    min_y = std::min(min_y, frame_rect.pos.y - frame_rect.height / 2);
  }
  return {(max_x + min_x) / 2, (max_y + min_y) / 2};
}
