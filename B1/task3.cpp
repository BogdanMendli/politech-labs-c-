#include <memory>
#include <stdexcept>
#include "declarations.hpp"

void runTask3()
{
  std::vector<int> vector;
  int number = 0;
  bool met_zero = false;

  while (std::cin >> number)
  {
    if (number == 0)
    {
      met_zero = true;
      break;
    }

    vector.push_back(number);
  }

  if (!std::cin.eof() && std::cin.fail())
  {
    throw std::ios_base::failure("fail reading data, task3");
  }

  if (vector.empty())
  {
    return;
  }

  if (!met_zero)
  {
    throw std::runtime_error("No zero.");
  }

  switch (vector.back())
  {
    case 1:
      for (auto i = vector.begin(); i != vector.end();)
      {
        i = ((*i % 2) == 0) ? vector.erase(i) : ++i;
      }
      break;

    case 2:
      for (auto i = vector.begin(); i != vector.end();)
      {
        i = ((*i % 3) == 0) ? (vector.insert(++i, 3, 1) + 3) : ++i;
      }
      break;

    default:
      break;
  }
  printContainerValues(vector);
}
