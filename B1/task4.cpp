#include <random>
#include <stdexcept>
#include "declarations.hpp"

void fillRandom(double *arr, int size)
{
  std::mt19937 rng(std::random_device{}());
  std::uniform_real_distribution<double> dist(-1.0, 1.0);
  for (int i = 0; i < size; i++)
  {
    arr[i] = dist(rng);
  }
}

void runTask4(const char *numbers, const char *direction)
{
  sortOrder order = getSortOrder(numbers);

  std::vector<double> vector(static_cast<unsigned int>(std::stoi(direction)));
  if(!vector.empty())
  {
    fillRandom(&vector[0], vector.size());
    printContainerValues(vector);
    sort<bracketsImplementation>(vector, order);
    printContainerValues(vector);
  }
}
