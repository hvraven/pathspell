#ifndef LIBRPG_XMLDECODE_H
#define LIBRPG_XMLDECODE_H 1

#include "xml.h"

namespace RPG
{
  std::string text_to_string(const TiXmlElement *const pelem);

  bool attribute_to_bool(const std::string& attribute,
                         const TiXmlElement *const pelem,
                         bool default_value = false);
  int attribute_to_int(const std::string& attribute,
                       const TiXmlElement *const pelem);
  std::string attribute_to_string(const std::string& attribute,
                                  const TiXmlElement *const pelem);
}

#endif /* LIBRPG_XMLDECODE_H */
