#include <functional>
#include <algorithm>
#include <sstream>
#include <map>
#include "queue-with-priority.hpp"

void parseAddArguments(QueueWithPriority<std::string> &queue, std::stringstream &input);
void parseGetArguments(QueueWithPriority<std::string> &queue, std::stringstream &in);
void parseAccelerateArguments(QueueWithPriority<std::string> &queue, std::stringstream &in);

void task1()
{
  using executeCommand = std::function<void(QueueWithPriority<std::string> &, std::stringstream &)>;

  std::map<const std::string, executeCommand> commands =
    {
      {"add",        parseAddArguments},
      {"get",        parseGetArguments},
      {"accelerate", parseAccelerateArguments}
    };

  QueueWithPriority<std::string> queue;

  std::string line;

  while (std::getline(std::cin, line))
  {
    std::stringstream lineStream(line);
    std::string command_name;
    lineStream >> command_name;

    auto check = [&](const std::pair<const std::string, executeCommand> &pair)
    { return (pair.first == command_name); };

    auto command = std::find_if(std::begin(commands), std::end(commands), check);

    if (command != std::end(commands))
    {
      command->second(queue, lineStream);
    }
    else
    {
      std::cout << "<INVALID COMMAND>\n";
    }
  }
}
