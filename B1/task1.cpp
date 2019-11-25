#include "declarations.hpp"
#include <stdexcept>

void runTask1(const char *direction)
{
  sortOrder order = getSortOrder(direction);

  std::forward_list<int>list1;
  int next_value;
  while (std::cin >> next_value)
  {
    list1.push_front(next_value);
  }
  if (std::cin.fail() && !std::cin.eof())
  {
    throw std::invalid_argument("Incorrect input.");
  }

  std::vector<int>vector1(list1.begin(), list1.end());
  std::vector<int>vector2(list1.begin(), list1.end());

  sort<iteratorImplementation>(list1, order);
  printContainerValues(list1);

  sort<bracketsImplementation>(vector1, order);
  printContainerValues(vector1);

  sort<atImplementation>(vector2, order);
  printContainerValues(vector2);
}
