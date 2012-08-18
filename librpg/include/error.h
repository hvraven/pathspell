#ifndef LIBRPG_ERROR_H
#define LIBRPG_ERROR_H

#include <stdexcept>

namespace RPG
{
  struct xml_error : public std::logic_error
  {
    xml_error(const std::string& what)
      : std::logic_error(what) {}
  };
}

#endif /* LIBRPG_ERROR_H */
