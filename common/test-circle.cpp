#include <stdexcept>
#include <iostream>
#include <cmath>
#include <boost/test/auto_unit_test.hpp>
#include "circle.hpp"

BOOST_AUTO_TEST_SUITE(TestForCircle)

const double INACCURACY = 0.001;

BOOST_AUTO_TEST_CASE(immutabilityRadiusAfterMovingCenter)
{
  maschenko::Circle test_circle({15, 15}, 5);
  const double radius = test_circle.getRadius();
  test_circle.move({50, 50});
  BOOST_CHECK_CLOSE(test_circle.getRadius(), radius, INACCURACY);
}

BOOST_AUTO_TEST_CASE(immutabilityRadiusAfterMovingOnDxAndDy)
{
  maschenko::Circle test_circle({15, 15}, 5);
  const double radius = test_circle.getRadius();
  test_circle.move(10, 10);
  BOOST_CHECK_CLOSE(test_circle.getRadius(), radius, INACCURACY);
}

BOOST_AUTO_TEST_CASE(immutabilityAreaAfterMovingCenter)
{
  maschenko::Circle test_circle({15, 15}, 5);
  const double area = test_circle.getArea();
  test_circle.move({50, 50});
  BOOST_CHECK_CLOSE(test_circle.getArea(), area, INACCURACY);
}

BOOST_AUTO_TEST_CASE(immutabilityAreaAfterMovingOnDxAndDy)
{
  maschenko::Circle test_circle({15, 15}, 5);
  const double area = test_circle.getArea();
  test_circle.move(10, 10);
  BOOST_CHECK_CLOSE(test_circle.getArea(), area, INACCURACY);
}

BOOST_AUTO_TEST_CASE(AreaScalingIncrease)
{
  maschenko::Circle test_circle {{15, 15}, 5};
  const double area = test_circle.getArea();
  const double increase_number = 3;
  test_circle.scale(increase_number);
  BOOST_CHECK_CLOSE(test_circle.getArea(), increase_number * increase_number * area, INACCURACY);
}

BOOST_AUTO_TEST_CASE(AreaScalingDecrease)
{
  maschenko::Circle test_circle {{15, 15}, 5};
  const double area = test_circle.getArea();
  const double decrease_number = 0.25;
  test_circle.scale(decrease_number);
  BOOST_CHECK_CLOSE(test_circle.getArea(), area * decrease_number * decrease_number, INACCURACY);
}

BOOST_AUTO_TEST_CASE(ThrowExceptionAfterScale)
{
  maschenko::Circle test_circle {{15, 15}, 5};
  BOOST_CHECK_THROW(test_circle.scale(-10), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(ThrowExceptionDueIncorrectRadius)
{
  BOOST_CHECK_THROW(maschenko::Circle test_circle({15, 15}, -5), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(immutabilityCenterAfterRotating)
{
  maschenko::Circle circle({10, 10}, 20);
  const maschenko::point_t center = circle.getCenter();

  circle.rotate(M_PI / 2);
  BOOST_CHECK_CLOSE(center.x, circle.getCenter().x, INACCURACY);
  BOOST_CHECK_CLOSE(center.y, circle.getCenter().y, INACCURACY);
}

BOOST_AUTO_TEST_CASE(immutabilityAreaAfterRotating)
{
  maschenko::Circle circle({10, 10}, 20);
  const double area = circle.getArea();

  circle.rotate(M_PI / 2);
  BOOST_CHECK_CLOSE(area, circle.getArea(), INACCURACY);
}

BOOST_AUTO_TEST_CASE(immutabilityFrameRectAfterRotating360)
{
  maschenko::Circle circle({10, 10}, 30);
  const double width = circle.getFrameRect().width;
  const double height = circle.getFrameRect().height;

  circle.rotate(2 * M_PI);
  BOOST_CHECK_CLOSE(width, circle.getFrameRect().width, INACCURACY);
  BOOST_CHECK_CLOSE(height, circle.getFrameRect().height, INACCURACY);
}

BOOST_AUTO_TEST_CASE(swapSidesOfFrameRectAfterRotating90)
{
  maschenko::Circle circle({10, 10}, 20);
  const double width = circle.getFrameRect().width;
  const double height = circle.getFrameRect().height;

  circle.rotate(M_PI / 2);
  BOOST_CHECK_CLOSE(width, circle.getFrameRect().height, INACCURACY);
  BOOST_CHECK_CLOSE(height, circle.getFrameRect().width, INACCURACY);
}

BOOST_AUTO_TEST_CASE(correctWorkingMethodGetCenter)
{
  maschenko::point_t center = {10, 10};
  maschenko::Circle circle(center, 20);

  BOOST_CHECK_CLOSE(center.x, circle.getCenter().x, INACCURACY);
  BOOST_CHECK_CLOSE(center.y, circle.getCenter().y, INACCURACY);
}

BOOST_AUTO_TEST_SUITE_END()
