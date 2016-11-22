#include "logger.hpp"
#include "constants.hpp"

std::string onlyFile(std::string longName)
{
  auto it = longName.find_last_of('\\');
  return longName.erase(0, it + 1);
}
SimpleLogger & logger = SimpleLogger::Instance();
