#include <iostream>
#include "shape.hpp"
#include "circle.hpp"
#include "rectangle.hpp"

int main()
{
  std::cout << "new Circle with center: (14;56) and radius = 5" << std::endl;
  maschenko::Circle circle({14, 56}, 5);
  maschenko::Shape *p_circle = &circle;
  p_circle->writeInfo();
  std::cout << "move Circle in point with center: (-34,32)" << std::endl;
  p_circle->move({-34, 32});
  p_circle->writeInfo();
  std::cout << "move Circle at the dx = 2, dy = -4" << std::endl;
  p_circle->move(2, -4);
  p_circle->writeInfo();
  std::cout << "scale circle with coefficient = 3" << std::endl;
  p_circle->scale(3);
  p_circle->writeInfo();

  std::cout << "---------------------------------------------" << std::endl << std::endl;

  std::cout << "new Rectangle with center (-5;32) and width 2, height = 7" << std::endl;
  maschenko::Rectangle rectangle({-5, 32}, 2, 7);
  maschenko::Shape *p_rect = &rectangle;
  p_rect->writeInfo();
  std::cout << "move Rectangle in point with center (-37,-37)" << std::endl;
  p_rect->move({-37, -37});
  p_rect->writeInfo();
  std::cout << "move Rectangle at the dx = 7, dy = 0" << std::endl;
  p_rect->move(7, 0);
  p_rect->writeInfo();
  std::cout << "scale circle with coefficient = 4" << std::endl;
  p_rect->scale(4);
  p_rect->writeInfo();
  return 0;
}
