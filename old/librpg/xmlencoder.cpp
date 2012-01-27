#include "xml.h"

/**
 * \brief function to create a TiXmlElement from a Name
 * \todo add support for multiple languages
 */
TiXmlElement encode_name( const Name& name )
{
  TiXmlElement result;
  result.SetAttribute("language", "en");
  result.Value(name.print());
  return result;
}
