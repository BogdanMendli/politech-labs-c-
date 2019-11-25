#ifndef A3_COMPOSITE_SHAPE_HPP
#define A3_COMPOSITE_SHAPE_HPP

#include <memory>
#include "shape.hpp"

namespace maschenko
{
  class CompositeShape : public Shape
  {
  public:
    using p_shape = std::shared_ptr<Shape>;

    CompositeShape();
    CompositeShape(const CompositeShape &cs);
    CompositeShape(CompositeShape &&cs);
    ~CompositeShape() = default;

    CompositeShape& operator =(const CompositeShape& rhs);
    CompositeShape& operator =(CompositeShape&& rhs);

    p_shape operator [](size_t index) const;

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(double dx, double dy) override;
    void move(const maschenko::point_t &center) override;
    void scale(double coefficient) override;
    void writeInfo() const override;
    size_t getShapeCount() const;
    void add(p_shape shape);
    void remove(p_shape shape);
    void remove(size_t index);
    void rotate (const double angle) override;
    point_t getCenter() const override;

  private:
    size_t shape_count_;
    std::unique_ptr<p_shape[]> shape_array_;
  };
}

#endif //A3_COMPOSITE_SHAPE_HPP
