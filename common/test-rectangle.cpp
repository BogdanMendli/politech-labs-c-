#include <stdexcept>
#include <iostream>
#include <cmath>
#include <boost/test/auto_unit_test.hpp>
#include "rectangle.hpp"

BOOST_AUTO_TEST_SUITE(TestForRectangle)

const double INACCURACY = 0.001;

BOOST_AUTO_TEST_CASE(immutabilityWidthAfterMovingCenter)
{
  maschenko::Rectangle test_rectangle({10, 10}, 5, 8);
  const double width = test_rectangle.getFrameRect().width;
  test_rectangle.move({50, 50});
  BOOST_CHECK_CLOSE(test_rectangle.getFrameRect().width, width, INACCURACY);
}

BOOST_AUTO_TEST_CASE(immutabilityWidthAfterMovingOnDxAndDY)
{
  maschenko::Rectangle test_rectangle({10, 10}, 5, 8);
  const double width = test_rectangle.getFrameRect().width;
  test_rectangle.move(10, 10);
  BOOST_CHECK_CLOSE(test_rectangle.getFrameRect().width, width, INACCURACY);
}

BOOST_AUTO_TEST_CASE(immutabilityHeightAfterMovingCenter)
{
  maschenko::Rectangle test_rectangle({10, 10}, 5, 8);
  const double height = test_rectangle.getFrameRect().height;
  test_rectangle.move({50, 50});
  BOOST_CHECK_CLOSE(test_rectangle.getFrameRect().height, height, INACCURACY);
}

BOOST_AUTO_TEST_CASE(immutabilityHeightAfterMovingOnDxAndDy)
{
  maschenko::Rectangle test_rectangle({10, 10}, 5, 8);
  const double height = test_rectangle.getFrameRect().height;
  test_rectangle.move(10, 10);
  BOOST_CHECK_CLOSE(test_rectangle.getFrameRect().height, height, INACCURACY);
}

BOOST_AUTO_TEST_CASE(immutabilityAreaAfterMovingCenter)
{
  maschenko::Rectangle test_rectangle({10, 10}, 5, 8);
  const double area = test_rectangle.getArea();
  test_rectangle.move({50, 50});
  BOOST_CHECK_CLOSE(test_rectangle.getArea(), area, INACCURACY);
}

BOOST_AUTO_TEST_CASE(immutabilityAreaAfterMovingOnDxAndDy)
{
  maschenko::Rectangle test_rectangle({10, 10}, 5, 8);
  const double area = test_rectangle.getArea();
  test_rectangle.move(10, 10);
  BOOST_CHECK_CLOSE(test_rectangle.getArea(), area, INACCURACY);
}

BOOST_AUTO_TEST_CASE(AreaScalingIncrease)
{
  maschenko::Rectangle test_rectangle {{10, 10}, 5, 8};
  const double area = test_rectangle.getArea();
  const double increase_number = 3;
  test_rectangle.scale(increase_number);
  BOOST_CHECK_CLOSE(test_rectangle.getArea(), increase_number * increase_number * area, INACCURACY);
}

BOOST_AUTO_TEST_CASE(AreaScalingDecrease)
{
  maschenko::Rectangle test_rectangle {{10, 10}, 5, 8};
  const double area = test_rectangle.getArea();
  const double decrease_number = 0.25;
  test_rectangle.scale(decrease_number);
  BOOST_CHECK_CLOSE(test_rectangle.getArea(), area * decrease_number * decrease_number, INACCURACY);
}

BOOST_AUTO_TEST_CASE(ScaleTest)
{
  maschenko::Rectangle test_rectangle {{ 10, 10}, 5, 8};
  BOOST_CHECK_THROW(test_rectangle.scale(-5), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(ThrowExceptionDueIncorrectWidth)
{
  BOOST_CHECK_THROW(maschenko::Rectangle test_rectangle ({10, 10}, -5, 8), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(ThrowExceptionDueIncorrectHeight)
{
  BOOST_CHECK_THROW(maschenko::Rectangle test_rectangle ({10, 10}, 5, -8), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(immutabilityCenterAfterRotating)
{
  maschenko::Rectangle rectangle({10, 10}, 20, 30);
  const maschenko::point_t center = rectangle.getCenter();

  rectangle.rotate(M_PI / 2);
  BOOST_CHECK_CLOSE(center.x, rectangle.getCenter().x, INACCURACY);
  BOOST_CHECK_CLOSE(center.y, rectangle.getCenter().y, INACCURACY);
}

BOOST_AUTO_TEST_CASE(immutabilityAreaAfterRotating)
{
  maschenko::Rectangle rectangle({10, 10}, 20, 30);
  const double area = rectangle.getArea();

  rectangle.rotate(M_PI / 2);
  BOOST_CHECK_CLOSE(area, rectangle.getArea(), INACCURACY);
}

BOOST_AUTO_TEST_CASE(immutabilityFrameRectAfterRotating360)
{
  maschenko::Rectangle rectangle({10, 10}, 20, 30);
  const double width = rectangle.getFrameRect().width;
  const double height = rectangle.getFrameRect().height;

  rectangle.rotate(2 * M_PI);
  BOOST_CHECK_CLOSE(width, rectangle.getFrameRect().width, INACCURACY);
  BOOST_CHECK_CLOSE(height, rectangle.getFrameRect().height, INACCURACY);
}

BOOST_AUTO_TEST_CASE(swapSidesOfFrameRectAfterRotating90)
{
  maschenko::Rectangle rectangle({10, 10}, 20, 30);
  const double width = rectangle.getFrameRect().width;
  const double height = rectangle.getFrameRect().height;

  rectangle.rotate(M_PI / 2);
  BOOST_CHECK_CLOSE(width, rectangle.getFrameRect().height, INACCURACY);
  BOOST_CHECK_CLOSE(height, rectangle.getFrameRect().width, INACCURACY);
}

BOOST_AUTO_TEST_CASE(correctWorkingMethodGetCenter)
{
  maschenko::point_t center = {10, 10};
  maschenko::Rectangle rectangle(center, 20, 30);

  BOOST_CHECK_CLOSE(center.x, rectangle.getCenter().x, INACCURACY);
  BOOST_CHECK_CLOSE(center.y, rectangle.getCenter().y, INACCURACY);
}

BOOST_AUTO_TEST_SUITE_END()
