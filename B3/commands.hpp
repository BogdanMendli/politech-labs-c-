#ifndef B3_COMMANDS_HPP
#define B3_COMMANDS_HPP

#include <functional>
#include <istream>
#include "bookmarkManager.hpp"

namespace commands
{
  using insert_position = BookmarkManager::InsertPosition;
  using move_position = BookmarkManager::MovePosition;
  using execute_command = std::function<void(BookmarkManager&, std::ostream&)>;

  execute_command parseTaskArguments(std::istream& input);

  execute_command parseAddArguments(std::istream& input);
  execute_command parseStoreArguments(std::istream& input);
  execute_command parseInsertArguments(std::istream& input);
  execute_command parseDeleteArguments(std::istream& input);
  execute_command parseShowArguments(std::istream& input);
  execute_command parseMoveArguments(std::istream& input);
}

namespace detail
{
  std::string readBookmarkFromStream(std::istream& input);
  std::string readNumberFromStream(std::istream& input);
  std::string readNameFromStream(std::istream& input);
}

#endif
