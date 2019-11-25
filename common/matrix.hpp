#ifndef A2_MATRIX_HPP
#define A2_MATRIX_HPP

#include <memory>
#include "shape.hpp"

namespace maschenko
{
  class Matrix
  {
  public:
    using p_shape = std::shared_ptr<Shape>;

    Matrix();
    Matrix(const Matrix &matrix);
    Matrix(Matrix &&matrix);
    ~Matrix() = default;

    Matrix& operator =(const Matrix &rhs);
    Matrix& operator =(Matrix &&rhs);

    std::unique_ptr<p_shape[]> operator [](size_t index) const;
    bool operator ==(const Matrix &rhs) const;
    bool operator !=(const Matrix &rhs) const;

    void add(p_shape shape, const pair_t &pair);
    void writeInfo() const;
    size_t getLines() const;
    size_t getColumns() const;

  private:
    size_t lines_;
    size_t columns_;
    std::unique_ptr<p_shape[]> shape_matrix_;
  };
}

#endif //A2_MATRIX_HPP
