#include <stdexcept>
#include <iostream>
#include <cmath>
#include <boost/test/auto_unit_test.hpp>
#include "composite-shape.hpp"
#include "partition.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include "matrix.hpp"

using p_shape = std::shared_ptr<maschenko::Shape>;

BOOST_AUTO_TEST_SUITE(testImplementationOfMatrix)

BOOST_AUTO_TEST_CASE(quantityOfLayers)
{
  maschenko::point_t center = {0, 0};
  maschenko::Circle circle1(center, 5);
  maschenko::Circle circle2(center, 7);
  maschenko::Rectangle rect1(center, 5, 10);
  maschenko::Rectangle rect2(center, 8, 12);
  p_shape p_circle1 = std::make_shared<maschenko::Circle>(circle1);
  p_shape p_circle2 = std::make_shared<maschenko::Circle>(circle2);
  p_shape p_rect1 = std::make_shared<maschenko::Rectangle>(rect1);
  p_shape p_rect2 = std::make_shared<maschenko::Rectangle>(rect2);
  const size_t quantity_layers = 4;

  maschenko::CompositeShape composite_shape;
  composite_shape.add(p_rect1);
  composite_shape.add(p_rect2);
  composite_shape.add(p_circle1);
  composite_shape.add(p_circle2);
  maschenko::Matrix matrix = maschenko::part(composite_shape);


  BOOST_CHECK_EQUAL(quantity_layers, matrix.getLines());
}

BOOST_AUTO_TEST_CASE(quantityOfColumns)
{
  maschenko::Circle circle1({-100, -100}, 1);
  maschenko::Circle circle2({1000, -1000}, 1);
  maschenko::Rectangle rect1({0, 0}, 1, 1);
  maschenko::Rectangle rect2({100, 100}, 1, 1);
  p_shape p_circle1 = std::make_shared<maschenko::Circle>(circle1);
  p_shape p_circle2 = std::make_shared<maschenko::Circle>(circle2);
  p_shape p_rect1 = std::make_shared<maschenko::Rectangle>(rect1);
  p_shape p_rect2 = std::make_shared<maschenko::Rectangle>(rect2);
  const size_t quantity_columns = 4;

  maschenko::CompositeShape composite_shape;
  composite_shape.add(p_rect1);
  composite_shape.add(p_rect2);
  composite_shape.add(p_circle1);
  composite_shape.add(p_circle2);
  maschenko::Matrix matrix = maschenko::part(composite_shape);

  BOOST_CHECK_EQUAL(quantity_columns, matrix.getColumns());
}

BOOST_AUTO_TEST_CASE(extendsColumnsAndLines)
{
  maschenko::point_t center1 = {14, 56};
  maschenko::point_t center2 = {-53, 123};
  maschenko::point_t center3 = {59, -68};
  maschenko::point_t center4 = {39, -58};

  maschenko::Circle circle1(center1, 5);
  maschenko::Circle circle2(center2, 9);
  maschenko::Circle circle3(center3, 13);
  maschenko::Rectangle rect1(center1, 2, 7);
  maschenko::Rectangle rect2(center4, 8, 10);
  maschenko::Rectangle rect3(center3, 5, 15);

  p_shape p_circle1 = std::make_shared<maschenko::Circle>(circle1);
  p_shape p_circle2 = std::make_shared<maschenko::Circle>(circle2);
  p_shape p_circle3 = std::make_shared<maschenko::Circle>(circle3);
  p_shape p_rect1 = std::make_shared<maschenko::Rectangle>(rect1);
  p_shape p_rect2 = std::make_shared<maschenko::Rectangle>(rect2);
  p_shape p_rect3 = std::make_shared<maschenko::Rectangle>(rect3);
  const size_t lines = 2;
  const size_t columns = 4;

  maschenko::CompositeShape composite_shape;
  composite_shape.add(p_circle1);
  composite_shape.add(p_rect1);
  composite_shape.add(p_circle2);
  composite_shape.add(p_rect2);
  composite_shape.add(p_circle3);
  composite_shape.add(p_rect3);
  maschenko::Matrix matrix = maschenko::part(composite_shape);

  BOOST_CHECK_EQUAL(lines, matrix.getLines());
  BOOST_CHECK_EQUAL(columns, matrix.getColumns());
}

BOOST_AUTO_TEST_CASE(throwExceptionDuaDoesntExistShape)
{
  maschenko::point_t center = {0, 0};
  maschenko::Circle circle1(center, 5);
  maschenko::Circle circle2(center, 7);
  maschenko::Rectangle rect1(center, 5, 10);
  maschenko::Rectangle rect2(center, 8, 12);
  p_shape p_circle1 = std::make_shared<maschenko::Circle>(circle1);
  p_shape p_circle2 = std::make_shared<maschenko::Circle>(circle2);
  p_shape p_rect1 = std::make_shared<maschenko::Rectangle>(rect1);
  p_shape p_rect2 = std::make_shared<maschenko::Rectangle>(rect2);

  maschenko::CompositeShape composite_shape;
  composite_shape.add(p_rect1);
  composite_shape.add(p_rect2);
  composite_shape.add(p_circle1);
  composite_shape.add(p_circle2);
  maschenko::Matrix matrix = maschenko::part(composite_shape);

  BOOST_CHECK_THROW(matrix[matrix.getLines() + 5][matrix.getColumns() + 5], std::out_of_range);
}

BOOST_AUTO_TEST_CASE(copyingAndMovingConstructor)
{
  maschenko::Circle circle({0, 0}, 5);
  maschenko::Rectangle rect({10, 10}, 20, 30);
  p_shape p_circle = std::make_shared<maschenko::Circle>(circle);
  p_shape p_rect = std::make_shared<maschenko::Rectangle>(rect);
  maschenko::CompositeShape composite_shape;
  composite_shape.add(p_rect);
  composite_shape.add(p_circle);
  maschenko::Matrix matrix = maschenko::part(composite_shape);

  maschenko::Matrix matrix_copying(matrix);
  BOOST_CHECK_EQUAL(matrix_copying.getLines(), matrix.getLines());
  BOOST_CHECK_EQUAL(matrix_copying.getColumns(), matrix.getColumns());
  BOOST_CHECK(matrix == matrix_copying);

  maschenko::Matrix matrix_moving(std::move(matrix));
  BOOST_CHECK_EQUAL(matrix_copying.getLines(), matrix_moving.getLines());
  BOOST_CHECK_EQUAL(matrix_copying.getColumns(), matrix_moving.getColumns());
  BOOST_CHECK(matrix_moving == matrix_copying);
}

BOOST_AUTO_TEST_CASE(correctWorkingOperators)
{
  maschenko::point_t center1 = {14, 56};
  maschenko::point_t center2 = {-53, 123};
  maschenko::point_t center3 = {39, -58};
  maschenko::point_t center4 = {59, -68};

  maschenko::Circle circle1(center1, 5);
  maschenko::Circle circle2(center2, 9);
  maschenko::Circle circle3(center4, 13);
  maschenko::Circle circle4(center1, 10);
  maschenko::Rectangle rect1(center1, 2, 7);
  maschenko::Rectangle rect2(center3, 8, 10);
  maschenko::Rectangle rect3(center4, 5, 15);
  maschenko::Rectangle rect4(center1, 3, 5);

  p_shape p_circle1 = std::make_shared<maschenko::Circle>(circle1);
  p_shape p_circle2 = std::make_shared<maschenko::Circle>(circle2);
  p_shape p_circle3 = std::make_shared<maschenko::Circle>(circle3);
  p_shape p_circle4 = std::make_shared<maschenko::Circle>(circle4);
  p_shape p_rect1 = std::make_shared<maschenko::Rectangle>(rect1);
  p_shape p_rect2 = std::make_shared<maschenko::Rectangle>(rect2);
  p_shape p_rect3 = std::make_shared<maschenko::Rectangle>(rect3);
  p_shape p_rect4 = std::make_shared<maschenko::Rectangle>(rect4);

  maschenko::CompositeShape composite_shape;
  composite_shape.add(p_circle1);
  composite_shape.add(p_rect1);
  composite_shape.add(p_circle2);
  composite_shape.add(p_rect2);
  composite_shape.add(p_circle3);
  composite_shape.add(p_rect3);
  maschenko::Matrix matrix = maschenko::part(composite_shape);

  BOOST_CHECK(matrix[0][0] == p_circle1);
  BOOST_CHECK(matrix[0][1] == p_circle2);
  BOOST_CHECK(matrix[0][2] == p_rect2);
  BOOST_CHECK(matrix[0][3] == p_circle3);
  BOOST_CHECK(matrix[1][0] == p_rect1);
  BOOST_CHECK(matrix[1][1] == p_rect3);
  BOOST_CHECK(matrix[0][0] != p_rect3);
  BOOST_CHECK(matrix[1][0] != p_rect4);
  BOOST_CHECK(matrix[0][3] != p_circle4);

  maschenko::CompositeShape composite_shape1;
  maschenko::CompositeShape composite_shape2;
  composite_shape.add(p_circle1);
  composite_shape.add(p_rect1);
  composite_shape.add(p_circle2);
  composite_shape.add(p_rect2);
  composite_shape.add(p_circle3);
  composite_shape.add(p_rect3);
  maschenko::Matrix matrix1 = maschenko::part(composite_shape1);
  maschenko::Matrix matrix2 = maschenko::part(composite_shape2);

  BOOST_CHECK(matrix1 != matrix2);
  BOOST_CHECK(matrix1 != matrix);
  BOOST_CHECK(matrix != matrix2);

  matrix1 = matrix;
  BOOST_CHECK(matrix1 == matrix);
}

BOOST_AUTO_TEST_SUITE_END()
