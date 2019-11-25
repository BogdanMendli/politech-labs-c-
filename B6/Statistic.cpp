#include "Statistic.hpp"
#include <limits>
#include <stdexcept>

Statistics::Statistics() :
  m_Min(std::numeric_limits<int>::max()),
  m_Max(std::numeric_limits<int>::min()),
  m_OddSum(0),
  m_EvenSum(0),
  m_First(0),
  m_Count(0),
  m_PositiveCount(0),
  m_NegativeCount(0),
  m_Equality(false)
{
}

void Statistics::operator()(long long int num)
{
  if (num > m_Max)
  {
    m_Max = num;
  }
  if (num < m_Min)
  {
    m_Min = num;
  }

  if (num > 0)
  {
    m_PositiveCount++;
  }
  else if (num < 0)
  {
    m_NegativeCount++;
  }

  if (num % 2 == 0)
  {
    m_EvenSum+=num;
  }
  else
  {
    m_OddSum+=num;
  }

  if (m_Count == 0)
  {
    m_First = num;
  }

  if (num == m_First)
  {
    m_Equality = true;
  }
  else
  {
    m_Equality = false;
  }

  m_Count++;
}

long long int Statistics::getMin()
{
  if (m_Count < 1)
  {
    throw std::logic_error("Not enough numbers for statistics");
  }
  return m_Min;
}

long long int Statistics::getMax()
{
  if (m_Count < 1)
  {
    throw std::logic_error("Not enough numbers for statistics");
  }
  return m_Max;
}

double Statistics::getMean()
{
  if (m_Count < 1)
  {
    throw std::logic_error("Not enough numbers for statistics");
  }
  long long int count = m_Count;

  return (m_OddSum + m_EvenSum) / count;
}

size_t Statistics::getPostiveCount()
{
  if (m_Count < 1)
  {
    throw std::logic_error("Not enough numbers for statistics");
  }
  return m_PositiveCount;
}

size_t Statistics::getNegativeCount()
{
  if (m_Count < 1)
  {
    throw std::logic_error("Not enough numbers for statistics");
  }
  return m_NegativeCount;
}

long long int Statistics::getOddSum()
{
  if (m_Count < 1)
  {
    throw std::logic_error("Not enough numbers for statistics");
  }
  return m_OddSum;
}

long long int Statistics::getEvenSum()
{
  if (m_Count < 1)
  {
    throw std::logic_error("Not enough numbers for statistics");
  }
  return m_EvenSum;
}

bool Statistics::isFLEqual()
{
  if (m_Count < 1)
  {
    throw std::logic_error("Not enough numbers for statistics");
  }
  return m_Equality;
}
