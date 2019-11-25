#include <iostream>
#include <memory>
#include <cmath>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"
#include "partition.hpp"

int main()
{
  std::cout << "new Circle with center: (14;56) and radius = 5" << std::endl;
  maschenko::Circle circle1({14, 56}, 5);
  maschenko::CompositeShape::p_shape p_circle1 = std::make_shared<maschenko::Circle>(circle1);
  std::cout << "new Circle with center: (-53;123) and radius = 9" << std::endl;
  maschenko::Circle circle2({-53, 123}, 9);
  maschenko::CompositeShape::p_shape p_circle2 = std::make_shared<maschenko::Circle>(circle2);
  std::cout << "new Circle with center: (59;-68) and radius = 13" << std::endl;
  maschenko::Circle circle3({59, -68}, 13);
  maschenko::CompositeShape::p_shape p_circle3 = std::make_shared<maschenko::Circle>(circle3);
  std::cout << "new Circle with center: (-78;-98) and radius = 10" << std::endl;
  maschenko::Circle circle4({-78, -98}, 10);
  maschenko::CompositeShape::p_shape p_circle4 = std::make_shared<maschenko::Circle>(circle4);

  std::cout << std::endl << "---------------------------------------------" << std::endl << std::endl;

  std::cout << "new Rectangle with center (10;50) and width 2, height = 7" << std::endl;
  maschenko::Rectangle rect1({10, 50}, 2, 7);
  maschenko::CompositeShape::p_shape p_rect1 = std::make_shared<maschenko::Rectangle>(rect1);
  std::cout << "new Rectangle with center (39;-58) and width 8, height = 10" << std::endl;
  maschenko::Rectangle rect2({39, -58}, 8, 10);
  maschenko::CompositeShape::p_shape p_rect2 = std::make_shared<maschenko::Rectangle>(rect2);
  std::cout << "new Rectangle with center (59;-72) and width 5, height = 15" << std::endl;
  maschenko::Rectangle rect3({59, -72}, 5, 15);
  maschenko::CompositeShape::p_shape p_rect3 = std::make_shared<maschenko::Rectangle>(rect3);
  std::cout << "new Rectangle with center (0;0) and width 3, height = 5" << std::endl;
  maschenko::Rectangle rect4({0, 0}, 3, 5);
  maschenko::CompositeShape::p_shape p_rect4 = std::make_shared<maschenko::Rectangle>(rect4);

  std::cout << std::endl << "---------------------------------------------" << std::endl;

  maschenko::CompositeShape composite_shape;
  composite_shape.add(p_circle1);
  composite_shape.add(p_circle2);
  composite_shape.add(p_circle3);
  composite_shape.add(p_circle4);
  composite_shape.add(p_rect1);
  composite_shape.add(p_rect2);
  composite_shape.add(p_rect3);
  composite_shape.add(p_rect4);
  composite_shape.writeInfo();

  std::cout << std::endl << "---------------------------------------------" << std::endl;

  maschenko::Matrix matrix = maschenko::part(composite_shape);
  matrix.writeInfo();

  std::cout << std::endl << "---------------------------------------------" << std::endl;

  composite_shape.rotate(M_PI / 2);
  composite_shape.writeInfo();
  composite_shape.scale(2);
  composite_shape.writeInfo();

  return 0;
}


