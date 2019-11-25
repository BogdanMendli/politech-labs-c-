#ifndef STATISTIC_HPP
#define STATISTIC_HPP

#include <cstdlib>

class Statistics
{
public:
  Statistics();
  void operator()(long long int);
  long long int getMin();
  long long int getMax();
  double getMean();
  size_t getPostiveCount();
  size_t getNegativeCount();
  long long int getOddSum();
  long long int getEvenSum();
  bool isFLEqual();

private:
  long long int m_Min, m_Max, m_OddSum, m_EvenSum, m_First;
  size_t m_Count, m_PositiveCount, m_NegativeCount;
  bool m_Equality;
};

#endif // STATISTIC_HPP
