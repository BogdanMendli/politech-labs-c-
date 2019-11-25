#include <boost/test/auto_unit_test.hpp>
#include "circle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"
#include "partition.hpp"
#include "rectangle.hpp"

using p_shape = std::shared_ptr<maschenko::Shape>;

BOOST_AUTO_TEST_SUITE(testImplementationOfPartition)

BOOST_AUTO_TEST_CASE(correctWorkingIsOverlapping)
{
  maschenko::point_t center1 = {-100, -100};
  maschenko::point_t center2 = {100, 100};

  maschenko::Rectangle rectangle1(center1, 2, 4);
  maschenko::Rectangle rectangle2(center1, 4, 5);
  maschenko::Circle circle(center2, 5);

  p_shape p_rect1 = std::make_shared<maschenko::Rectangle>(rectangle1);
  p_shape p_rect2 = std::make_shared<maschenko::Rectangle>(rectangle2);
  p_shape p_circle = std::make_shared<maschenko::Circle>(circle);

  BOOST_CHECK(!maschenko::isOverlapping(p_rect1, p_circle));
  BOOST_CHECK(maschenko::isOverlapping(p_rect1, p_rect2));
}

BOOST_AUTO_TEST_CASE(correctWorkingOfPart)
{
  maschenko::point_t center1 = {14, 56};
  maschenko::point_t center2 = {-53, 123};
  maschenko::point_t center3 = {59, -68};
  maschenko::point_t center4 = {39, -58};

  maschenko::Circle circle1(center1, 5);
  maschenko::Circle circle2(center2, 9);
  maschenko::Circle circle3(center3, 13);
  maschenko::Rectangle rectangle1(center1, 2, 7);
  maschenko::Rectangle rectangle2(center4, 8, 10);
  maschenko::Rectangle rectangle3(center3, 5, 15);
  const size_t lines = 2;
  const size_t columns = 4;

  p_shape p_rect1 = std::make_shared<maschenko::Rectangle>(rectangle1);
  p_shape p_rect2 = std::make_shared<maschenko::Rectangle>(rectangle2);
  p_shape p_rect3 = std::make_shared<maschenko::Rectangle>(rectangle3);
  p_shape p_circle1 = std::make_shared<maschenko::Circle>(circle1);
  p_shape p_circle2 = std::make_shared<maschenko::Circle>(circle2);
  p_shape p_circle3 = std::make_shared<maschenko::Circle>(circle3);

  maschenko::CompositeShape composite_shape;
  composite_shape.add(p_circle1);
  composite_shape.add(p_circle2);
  composite_shape.add(p_circle3);
  composite_shape.add(p_rect1);
  composite_shape.add(p_rect2);
  composite_shape.add(p_rect3);
  maschenko::Matrix matrix = maschenko::part(composite_shape);

  BOOST_CHECK_EQUAL(lines, matrix.getLines());
  BOOST_CHECK_EQUAL(columns, matrix.getColumns());

  BOOST_CHECK(matrix[0][0] == p_circle1);
  BOOST_CHECK(matrix[0][1] == p_circle2);
  BOOST_CHECK(matrix[0][2] == p_circle3);
  BOOST_CHECK(matrix[0][3] == p_rect2);
  BOOST_CHECK(matrix[1][0] == p_rect1);
  BOOST_CHECK(matrix[1][1] == p_rect3);
}

BOOST_AUTO_TEST_SUITE_END()
