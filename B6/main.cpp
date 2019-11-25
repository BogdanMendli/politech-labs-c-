#include <iostream>
#include <iterator>
#include <algorithm>
#include <stdexcept>
#include <functional>
#include "Statistic.hpp"

int main()
{
  Statistics Stats;

  std::for_each(std::istream_iterator<long long int>(std::cin), std::istream_iterator<long long int>(), std::ref(Stats));

  if (!std::cin.eof())
  {
    std::cerr <<"Non integral value" <<std::endl;
    return 1;
  }

  std::cout.precision(1);

  try
  {
    std::cout <<"Max: " <<Stats.getMax() <<std::endl;
    std::cout <<"Min: " <<Stats.getMin() <<std::endl;
    std::cout <<"Mean: " <<std::fixed <<Stats.getMean() <<std::endl;
    std::cout <<"Positive: " <<Stats.getPostiveCount() <<std::endl;
    std::cout <<"Negative: " <<Stats.getNegativeCount() <<std::endl;
    std::cout <<"Odd Sum: " <<Stats.getOddSum() <<std::endl;
    std::cout <<"Even Sum: " <<Stats.getEvenSum() <<std::endl;
    std::cout <<"First/Last Equal: ";
    Stats.isFLEqual()? std::cout <<"yes" : std::cout <<"no";
    std::cout <<std::endl;
  }
  catch (std::logic_error)
  {
    std::cout <<"No Data" <<std::endl;
    return 0;
  }

  return 0;
}
