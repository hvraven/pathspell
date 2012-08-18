#include "xmldecode.h"

#include "error.h"
#include "strmanip.h"

/**
 * @brief evaluates an attribute as bool
 * @param attribute attribute containing the bool
 * @param pelem element containing the attribute
 * @throws xml_error if read was not successfull
 *
 * This function evaluetes yes, true and 1 to true and no, false and 0
 * to false. Otherwise a xml_error is thrown.
 * If the attribute is empty the given default value is returned
 * (default: false)
 */
bool
RPG::attribute_to_bool(const std::string& attribute,
                       const TiXmlElement *const pelem,
                       bool default_value)
{
  std::string input = to_lower(attribute_to_string(attribute, pelem));
  if (input == "")
    return default_value;
  else if (input == "yes" || input == "true" || input == "1")
    return true;
  else if (input == "no" || input == "false" || input == "0")
    return false;
  else
    throw RPG::xml_error("failed to convert \"" + input +
                         "\" to a bool value");
}

/**
 * @brief reads an attribute as int
 * @param attribute attribute containing the int
 * @param pelem element containing the attribute
 * @return the value
 * @throws xml_error if read was not successfull
 */
int
RPG::attribute_to_int(const std::string& attribute,
                      const TiXmlElement *const pelem)
{
  int result;
  if (pelem->QueryIntAttribute(attribute, &result) == TIXML_SUCCESS)
    return result;
  else
    throw RPG::xml_error("failed to read int attribute \"" +
                         attribute + "\" from element");
}

/**
 * @brief reads an attribute as string
 * @param attribute attribute containing the text
 * @param pelem element containing the attribute
 * @return the text
 * @throws xml_error if read was not successfull
 */
std::string
RPG::attribute_to_string(const std::string& attribute,
                         const TiXmlElement *const pelem)
{
  std::string result;
  if (pelem->QueryStringAttribute(attribute.c_str(), &result) == TIXML_SUCCESS)
    return result;
  else
    throw RPG::xml_error("failed to read string attribute \"" +
                         attribute + "\" from element");
}
