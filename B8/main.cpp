#include <iostream>
#include "InputTask.hpp"
#include "OutputTask.hpp"

int main(int args, char * argv[])
{
  int width = 40;

  if (args > 1)
  {
    if (args != 3)
    {
      std::cerr << "Invalid number of arguments.";
      return 1;
    }
    else if (std::string(argv[1]) != "--line-width")
    {
      std::cerr << "Invalid arguments.";
      return 1;
    }
    else
    {
      width = std::stoi(argv[2]);
      if (width < 24)
      {
        std::cerr << "Invalid line width.";
        return 1;
      }
    }
  }

  try
  {
    InputParser parser(std::cin);
    parser.parseInput();

    std::list<element_t> vector(parser.begin(), parser.end());
    if (!trueOrder(vector))
    {
      std::cerr << "Invalid input.";
      return 1;
    }
    formatText(std::cout, static_cast<unsigned int>(width), vector);
  }

  catch (const std::invalid_argument &e)
  {
    std::cerr << e.what();
    return 1;
  }

  return 0;
}
