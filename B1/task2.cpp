#include <fstream>
#include <memory>
#include <stdexcept>
#include "declarations.hpp"


void runTask2(const char *filename)
{
  std::ifstream input(filename);
  if(!input.is_open())
  {
    throw std::invalid_argument("Incorrect filename for task #2.");
  }

  size_t size = 0;
  size_t content_capacity = 64;
  std::unique_ptr<char[], decltype(&free)> contents(static_cast<char *>(malloc(content_capacity)), free);

  while (input)
  {
    input.read(&contents[size], content_capacity - size);
    size += input.gcount();
    if (size == content_capacity)
    {
      content_capacity *= 2;
      auto temp_content = contents.release();
      contents.reset(static_cast<char *>(std::realloc(temp_content, content_capacity)));
      if (!contents) {
        throw std::runtime_error("Error allocate memory");
      }
    }
  }

  input.close();
  if(input.is_open())
  {
    throw std::ios_base::failure("Error close file");
  }

  std::vector<char> vector(&contents[0], &contents[size]);
  for (char &it : vector)
  {
    std::cout << it;
  }
}
