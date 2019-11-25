#include "OutputTask.hpp"
#include <list>

void printLine (std::ostream &out, const std::list<element_t> &line)
{
  for (const auto &it : line)
  {
    out << it.value;
  }
  out << "\n";
}

int reorganizeLine (std::ostream &out, std::list<element_t> &line)
{
  std::size_t width = 0;
  std::list<element_t>newLine;
  while (!line.empty())
  {
    newLine.push_front(line.back());
    width += line.back().value.size();
    line.pop_back();
    if (newLine.front().type == element_t::WORD || newLine.front().type == element_t::NUMBER)
    {
      break;
    }
  }
  printLine(out, line);
  line = newLine;
  return width;
}

void formatText (std::ostream &out, unsigned int width, const std::list<element_t> &vector)
{
  std::size_t currentWidth = 0;
  std::list<element_t> line;
  for (const auto &it : vector)
  {
    switch(it.type)
    {
      case element_t::MARK:
        if(currentWidth + 1 > width)
        {
          currentWidth = static_cast<size_t>(reorganizeLine(out, line));
        }
        line.push_back(it);
        currentWidth += it.value.size();
        break;

      case element_t::DASH:
        if(currentWidth + 4 > width)
        {
          currentWidth = static_cast<size_t>(reorganizeLine(out, line));
        }
        line.push_back(element_t { " ", element_t::SPACE });
        line.push_back(it);
        currentWidth += it.value.size() + 1;
        break;

      case element_t::WORD:
      case element_t::NUMBER:
        if(currentWidth + it.value.size() + 1 > width)
        {
          printLine(out, line);
          line.clear();
          currentWidth = 0;
        }
        else if(!line.empty())
        {
          line.push_back(element_t { " ", element_t::SPACE });
          currentWidth++;
        }
        line.push_back(it);
        currentWidth += it.value.size();
        break;
      case element_t::SPACE:
        break;
    }

  }
  if(!line.empty())
  {
    printLine(out, line);
  }
}

bool trueOrder(const std::list<element_t> &vector)
{
  if(!vector.empty() && (vector.front().type != element_t::WORD) && (vector.front().type != element_t::NUMBER))
  {
    return false;
  }
  for(auto it = vector.begin(); it != vector.end(); it++)
  {
    switch((*it).type)
    {
      case element_t::WORD:
      case element_t::NUMBER:
        if((*it).value.size() > 20)
        {
          return false;
        }
        break;
      case element_t::DASH:
        if((*it).value.size() != 3)
        {
          return false;
        }
        if(it != vector.begin())
        {
          const element_t &prev = *std::prev(it);
          if((prev.type == element_t::DASH) || ((prev.type == element_t::MARK) && (prev.value != ",")))
          {
            return false;
          }
        }
        break;
      case element_t::MARK:
        if(it != vector.begin())
        {
          const element_t &prev = *std::prev(it);
          if((prev.type == element_t::DASH) || (prev.type == element_t::MARK))
          {
            return false;
          }
        }
        break;
      case element_t::SPACE:
        break;
    }
  }
  return true;
}
