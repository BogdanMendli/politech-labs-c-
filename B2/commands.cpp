#include <map>
#include <sstream>
#include <algorithm>
#include "queue-with-priority.hpp"

void parseAddArguments(QueueWithPriority<std::string> &queue, std::stringstream &input)
{
  using priorityType = QueueWithPriority<std::string>::ElementPriority;

  std::map<const std::string, priorityType> priorities =
    {
      {"low",    priorityType::LOW},
      {"normal", priorityType::NORMAL},
      {"high",   priorityType::HIGH}
    };

  std::string priority_name;
  input >> std::ws >> priority_name;

  auto check = [&](const std::pair<const std::string, priorityType> &pair)
  {
    return (pair.first == priority_name);
  };

  auto argPriority = std::find_if(std::begin(priorities), std::end(priorities), check);

  if (argPriority == std::end(priorities))
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }

  std::string data;
  std::getline(input >> std::ws, data);

  if (data.empty())
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }

  queue.putElement(data, argPriority->second);
}

void parseGetArguments(QueueWithPriority<std::string> &queue, std::stringstream &in)
{
  std::string data;
  std::getline(in >> std::ws, data);

  if (!data.empty())
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }

  if (queue.empty())
  {
    std::cout << "<EMPTY>\n";
    return;
  }

  std::string element = queue.getElement();
  std::cout << element << "\n";
}

void parseAccelerateArguments(QueueWithPriority<std::string> &queue, std::stringstream &in)
{
  std::string data;
  std::getline(in >> std::ws, data);

  if (!data.empty())
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }

  queue.accelerate();
}

