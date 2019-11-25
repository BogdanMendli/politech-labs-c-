#include "declarations.hpp"
#include <stdexcept>
#include <string>

int main(int args, char *argv[])
{
  try
  {
    if ((args < 2) || (args > 4))
    {
      std::cerr << "The number of the task required." << std::endl;
      return 1;
    }
    int variant = std::stoi(argv[1]);
    switch (variant)
    {
      case 1:
        if (args != 3)
        {
          std::cerr << "Incorrect amount of parameters for task #1." << std::endl;
          return 1;
        }
        runTask1(argv[2]);
        break;
      case 2:
        if (args != 3)
        {
          std::cerr << "Incorrect number of arguments.\n";
          return 1;
        }

        runTask2(argv[2]);
        break;
      case 3:
        if (args != 2)
        {
          std::cerr << "Incorrect number of arguments.\n";
          return 1;
        }

        runTask3();
        break;
      case 4:
        if (args != 4)
        {
          std::cerr << "Incorrect number of arguments.\n";
          return 1;
        }

        runTask4(argv[2], argv[3]);
        break;
      default:
        std::cerr << "Wrong task number." << std::endl;
        return 1;
    }
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << std::endl;
    return 1;
  }
  return 0;
}
