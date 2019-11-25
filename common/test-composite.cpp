#include <stdexcept>
#include <iostream>
#include <cmath>
#include <boost/test/auto_unit_test.hpp>
#include "composite-shape.hpp"
#include "circle.hpp"
#include "rectangle.hpp"

const double INACCURACY = 0.001;

using p_shape = std::shared_ptr<maschenko::Shape>;

BOOST_AUTO_TEST_SUITE(testImplementationOfCompositeShape)

BOOST_AUTO_TEST_CASE(immutabilityAreaAfterMovingCenter)
{
  maschenko::Circle circle({5, 5}, 5);
  maschenko::Rectangle rect({5, 5}, 10, 5);
  p_shape p_circle = std::make_shared<maschenko::Circle>(circle);
  p_shape p_rect = std::make_shared<maschenko::Rectangle>(rect);

  maschenko::CompositeShape composite_shape;
  composite_shape.add(p_circle);
  composite_shape.add(p_rect);

  const double area = composite_shape.getArea();
  composite_shape.move({20, 20});
  BOOST_CHECK_CLOSE(area, composite_shape.getArea(), INACCURACY);
}

BOOST_AUTO_TEST_CASE(immutabilityAreaAfterMovingOnDxAndDy)
{
  maschenko::Circle circle({5, 5}, 5);
  maschenko::Rectangle rect({5, 5}, 10, 5);
  p_shape p_circle = std::make_shared<maschenko::Circle>(circle);
  p_shape p_rect = std::make_shared<maschenko::Rectangle>(rect);

  maschenko::CompositeShape composite_shape;
  composite_shape.add(p_circle);
  composite_shape.add(p_rect);

  const double area = composite_shape.getArea();
  composite_shape.move(20, 20);
  BOOST_CHECK_CLOSE(area, composite_shape.getArea(), INACCURACY);
}

BOOST_AUTO_TEST_CASE(correctWorkingRemove)
{
  maschenko::Circle circle({5, 5}, 5);
  maschenko::Rectangle rect1({5, 5}, 7, 7);
  maschenko::Rectangle rect2({5, 5}, 11, 4);
  maschenko::Rectangle rect3({5, 5}, 12, 1);
  p_shape p_circle = std::make_shared<maschenko::Circle>(circle);
  p_shape p_rect1 = std::make_shared<maschenko::Rectangle>(rect1);
  p_shape p_rect2 = std::make_shared<maschenko::Rectangle>(rect2);
  p_shape p_rect3 = std::make_shared<maschenko::Rectangle>(rect3);

  maschenko::CompositeShape composite_shape;
  composite_shape.add(p_circle);
  composite_shape.add(p_rect1);
  composite_shape.add(p_rect2);
  composite_shape.add(p_rect3);
  const int quantity_shape = composite_shape.getShapeCount();

  composite_shape.remove(p_rect1);
  const int quantity_shape_after_remove1 = composite_shape.getShapeCount();

  BOOST_CHECK_EQUAL(quantity_shape - 1, quantity_shape_after_remove1);
  BOOST_CHECK_THROW(composite_shape.remove(p_rect1), std::invalid_argument);
  BOOST_CHECK_THROW(composite_shape.remove(quantity_shape), std::out_of_range);

  composite_shape.remove(p_rect2);
  const int quantity_shape_after_remove2 = composite_shape.getShapeCount();

  BOOST_CHECK_EQUAL(quantity_shape_after_remove1 - 1, quantity_shape_after_remove2);
  BOOST_CHECK_THROW(composite_shape.remove(p_rect2), std::invalid_argument);
  BOOST_CHECK_THROW(composite_shape.remove(quantity_shape_after_remove1), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(throwExceptionDuaEntryNull)
{
  maschenko::CompositeShape composite_shape;
  BOOST_CHECK_THROW(composite_shape.add(nullptr), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(throwExceptionDuaAddNull)
{
  maschenko::Circle circle({5, 5}, 5);
  maschenko::Rectangle rect({5, 5}, 10, 5);
  p_shape p_circle = std::make_shared<maschenko::Circle>(circle);
  p_shape p_rect = std::make_shared<maschenko::Rectangle>(rect);

  maschenko::CompositeShape composite_shape;
  composite_shape.add(p_circle);
  composite_shape.add(p_rect);
  BOOST_CHECK_THROW(composite_shape.add(nullptr), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(AreaScalingIncrease)
{
  maschenko::Circle circle({5, 5}, 5);
  maschenko::Rectangle rect({5, 5}, 10, 5);
  p_shape p_circle = std::make_shared<maschenko::Circle>(circle);
  p_shape p_rect = std::make_shared<maschenko::Rectangle>(rect);

  maschenko::CompositeShape composite_shape;
  composite_shape.add(p_circle);
  composite_shape.add(p_rect);

  const double area = composite_shape.getArea();
  const double number_increase = 3;
  composite_shape.scale(number_increase);
  BOOST_CHECK_CLOSE(area * number_increase * number_increase, composite_shape.getArea(), INACCURACY);
}

BOOST_AUTO_TEST_CASE(AreaScalingDecrease)
{
  maschenko::Circle circle({5, 5}, 5);
  maschenko::Rectangle rect({5, 5}, 10, 5);
  p_shape p_circle = std::make_shared<maschenko::Circle>(circle);
  p_shape p_rect = std::make_shared<maschenko::Rectangle>(rect);

  maschenko::CompositeShape composite_shape;
  composite_shape.add(p_circle);
  composite_shape.add(p_rect);

  const double area = composite_shape.getArea();
  const double number_increase = 0.25;
  composite_shape.scale(number_increase);
  BOOST_CHECK_CLOSE(area * number_increase * number_increase, composite_shape.getArea(), INACCURACY);
}

BOOST_AUTO_TEST_CASE(throwExceptionDuaIncorrectCoefficient)
{
  maschenko::Circle circle({5, 5}, 5);
  maschenko::Rectangle rect({5, 5}, 10, 5);
  p_shape p_circle = std::make_shared<maschenko::Circle>(circle);
  p_shape p_rect = std::make_shared<maschenko::Rectangle>(rect);

  maschenko::CompositeShape composite_shape;
  composite_shape.add(p_circle);
  composite_shape.add(p_rect);
  BOOST_CHECK_THROW(composite_shape.scale(-10), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(immutabilityShapeQuantityAfterRotating)
{
  maschenko::Circle circle({0, 0}, 5);
  maschenko::Rectangle rect({10, 10}, 20, 30);
  p_shape p_circle = std::make_shared<maschenko::Circle>(circle);
  p_shape p_rect = std::make_shared<maschenko::Rectangle>(rect);
  maschenko::CompositeShape composite_shape;
  composite_shape.add(p_circle);
  composite_shape.add(p_rect);
  const int quantity_shape = composite_shape.getShapeCount();

  composite_shape.rotate(M_PI / 2);
  BOOST_CHECK_EQUAL(quantity_shape, composite_shape.getShapeCount());
}

BOOST_AUTO_TEST_CASE(immutabilityCenterAfterRotating)
{
  maschenko::Circle circle({0, 0}, 5);
  maschenko::Rectangle rect({10, 10}, 20, 30);
  p_shape p_circle = std::make_shared<maschenko::Circle>(circle);
  p_shape p_rect = std::make_shared<maschenko::Rectangle>(rect);
  maschenko::CompositeShape composite_shape;
  composite_shape.add(p_circle);
  composite_shape.add(p_rect);
  const maschenko::point_t center = composite_shape.getCenter();

  composite_shape.rotate(M_PI / 2);
  BOOST_CHECK_CLOSE(center.x, composite_shape.getCenter().x, INACCURACY);
  BOOST_CHECK_CLOSE(center.y, composite_shape.getCenter().y, INACCURACY);
}

BOOST_AUTO_TEST_CASE(immutabilityAreaAfterRotating)
{
  maschenko::Circle circle({0, 0}, 5);
  maschenko::Rectangle rect({10, 10}, 20, 30);
  p_shape p_circle = std::make_shared<maschenko::Circle>(circle);
  p_shape p_rect = std::make_shared<maschenko::Rectangle>(rect);
  maschenko::CompositeShape composite_shape;
  composite_shape.add(p_circle);
  composite_shape.add(p_rect);
  const double area = composite_shape.getArea();

  composite_shape.rotate(M_PI / 2);
  BOOST_CHECK_CLOSE(area, composite_shape.getArea(), INACCURACY);
}

BOOST_AUTO_TEST_CASE(immutabilityFrameRectAfterRotating360)
{
  maschenko::Circle circle({0, 0}, 5);
  maschenko::Rectangle rect({10, 10}, 20, 30);
  p_shape p_circle = std::make_shared<maschenko::Circle>(circle);
  p_shape p_rect = std::make_shared<maschenko::Rectangle>(rect);
  maschenko::CompositeShape composite_shape;
  composite_shape.add(p_circle);
  composite_shape.add(p_rect);
  const double width = composite_shape.getFrameRect().width;
  const double height = composite_shape.getFrameRect().height;

  composite_shape.rotate(2 * M_PI);
  BOOST_CHECK_CLOSE(width, composite_shape.getFrameRect().width, INACCURACY);
  BOOST_CHECK_CLOSE(height, composite_shape.getFrameRect().height, INACCURACY);
}

BOOST_AUTO_TEST_CASE(swapSidesOfFrameRectAfterRotating90)
{
  maschenko::Circle circle({0, 0}, 5);
  maschenko::Rectangle rect({10, 10}, 20, 30);
  p_shape p_circle = std::make_shared<maschenko::Circle>(circle);
  p_shape p_rect = std::make_shared<maschenko::Rectangle>(rect);
  maschenko::CompositeShape composite_shape;
  composite_shape.add(p_circle);
  composite_shape.add(p_rect);
  const double width = composite_shape.getFrameRect().width;
  const double height = composite_shape.getFrameRect().height;

  composite_shape.rotate(M_PI / 2);
  BOOST_CHECK_CLOSE(width, composite_shape.getFrameRect().height, INACCURACY);
  BOOST_CHECK_CLOSE(height, composite_shape.getFrameRect().width, INACCURACY);
}

BOOST_AUTO_TEST_SUITE_END()
