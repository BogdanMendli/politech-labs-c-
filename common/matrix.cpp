#include "matrix.hpp"
#include <stdexcept>
#include <iostream>
#include <cmath>

maschenko::Matrix::Matrix() :
  lines_(0),
  columns_(0),
  shape_matrix_()
{}

maschenko::Matrix::Matrix(const Matrix &matrix) :
  lines_(matrix.getLines()),
  columns_(matrix.getColumns()),
  shape_matrix_(std::make_unique<p_shape[]>(matrix.lines_ * matrix.columns_))
{
  for (size_t i = 0; i < (lines_ * columns_); ++i)
  {
    shape_matrix_[i] = matrix.shape_matrix_[i];
  }
}

maschenko::Matrix::Matrix(Matrix &&matrix) :
  lines_(matrix.lines_),
  columns_(matrix.columns_),
  shape_matrix_(std::move(matrix.shape_matrix_))
{}

maschenko::Matrix& maschenko::Matrix::operator =(const Matrix &rhs)
{
  if (this != &rhs)
  {
    lines_ = rhs.lines_;
    columns_ = rhs.columns_;
    std::unique_ptr<p_shape[]> new_shape_matrix(std::make_unique<p_shape[]>(rhs.lines_ * rhs.columns_));

    for (size_t i = 0; i < (lines_ * columns_); ++i)
    {
      new_shape_matrix[i] = rhs.shape_matrix_[i];
    }
    shape_matrix_.swap(new_shape_matrix);
  }

  return *this;
}

maschenko::Matrix& maschenko::Matrix::operator =(Matrix &&rhs)
{
  if (this != &rhs)
  {
    lines_ = rhs.lines_;
    columns_ = rhs.columns_;
    shape_matrix_ = std::move(rhs.shape_matrix_);
  }

  return *this;
}

std::unique_ptr<maschenko::Matrix::p_shape[]> maschenko::Matrix::operator[](size_t index) const
{
  if (index >= lines_)
  {
    throw std::out_of_range("Index out of range");
  }

  std::unique_ptr<p_shape[]> new_shape_matrix(std::make_unique<p_shape[]>(columns_));

  for (size_t i = 0; i < columns_; ++i)
  {
    new_shape_matrix[i] = shape_matrix_[index * columns_ + i];
  }

  return new_shape_matrix;
}

bool maschenko::Matrix::operator==(const Matrix &rhs) const
{
  if ((lines_ != rhs.lines_) || (columns_ != rhs.columns_))
  {
    return false;
  }

  for (size_t i = 0; i < (lines_ * columns_); ++i)
  {
    if (shape_matrix_[i] != rhs.shape_matrix_[i])
    {
      return false;
    }
  }

  return true;
}

bool maschenko::Matrix::operator!=(const Matrix &rhs) const
{
  if (this == &rhs)
  {
    return false;
  }

  return true;
}

void maschenko::Matrix::add(p_shape shape, const pair_t &pair)
{
  size_t lines = (lines_ == pair.line) ? (lines_ + 1) : (lines_);
  size_t columns = (columns_ == pair.column) ? (columns_ + 1) : (columns_);

  std::unique_ptr<p_shape[]> new_shape_matrix(std::make_unique<p_shape[]>(lines * columns));
  for (size_t i = 0; i < lines; ++i)
  {
    for (size_t j = 0; j < columns; ++j)
    {
      if ((lines_ == i) || (columns_ == j))
      {
        new_shape_matrix[i * columns + j] = nullptr;
      }
      else
      {
        new_shape_matrix[i * columns + j] = shape_matrix_[i * columns_ + j];
      }
    }
  }

  new_shape_matrix[pair.line * columns + pair.column] = shape;
  shape_matrix_.swap(new_shape_matrix);
  lines_ = lines;
  columns_ = columns;
}

void maschenko::Matrix::writeInfo() const
{
  std::cout << "In matrix exist " << lines_ << " lines and "
            << columns_ << " columns" << std::endl;
  for (size_t i = 0; i < lines_; ++i)
  {
    for (size_t j = 0; j < columns_; ++j)
    {
      if (shape_matrix_[i * columns_ + j] != nullptr)
      {
        std::cout << "On " << i + 1 << " layer, "
                  << j + 1 << " position is : " << std::endl;
        shape_matrix_[i * columns_ + j]->writeInfo();
        std::cout << std::endl << "*********************************" << std::endl << std::endl;
      }
    }
  }
}

size_t maschenko::Matrix::getLines() const
{
  return lines_;
}

size_t maschenko::Matrix::getColumns() const
{
  return columns_;
}
