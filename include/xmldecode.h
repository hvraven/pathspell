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

  /**
   * @brief get the text defined in a element as string
   * @param pelem element containing text
   * @return the text
   * @todo find a way to move that into xmldecode.cpp without linker error...
   *
   * text_to_string called to a element of the form <elem>testtext</elem>
   * will return "testtext"
   */
  inline std::string
  text_to_string(const TiXmlElement *const pelem)
  {
    return pelem->GetText();
  }
}

#endif /* LIBRPG_XMLDECODE_H */
