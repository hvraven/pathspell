#include "xmlspell.h"

#include "error.h"
#include "strmanip.h"
#include "xmldecode.h"
#include <cctype>
#include <map>

using namespace RPG;
using namespace RPG::Pathfinder;

/**
 * @brief function to initialize element translation map
 */
std::map<std::string, Spell_Token>
generate_elements_map()
{
  std::map<std::string, Spell_Token> elements;

  elements[ "name" ] = Spell_Token::Name;
  elements[ "school" ] = Spell_Token::School;
  elements[ "level" ] = Spell_Token::Level;
  elements[ "domain" ] = Spell_Token::Domain;
  elements[ "casting_time" ] = Spell_Token::Casting_Time;
  elements[ "component" ] = Spell_Token::Components;
  elements[ "range" ] = Spell_Token::Range;
  elements[ "duration" ] = Spell_Token::Duration;
  elements[ "saving_throw" ] = Spell_Token::Saving_Throw;
  elements[ "spell_resistance" ] = Spell_Token::Spell_Resistance;
  elements[ "short_description" ] = Spell_Token::Short_Description;
  elements[ "description" ] = Spell_Token::Description;
  elements[ "target" ] = Spell_Token::Target;
  elements[ "annotation" ] = Spell_Token::Annotation;
  elements[ "note" ] = Spell_Token::Note;
  elements[ "area" ] = Spell_Token::Area;

  return elements;
}

/**
 * @brief gets the xml data of a name element and writes it to the spell
 * @param spell the spell to save the name in
 * @param pelement pointer to the xml name entry
 * @todo set a global language and use it only if language matches
 * @todo add error handling
 *
 * reads the language attribute of the spell. If the language is en the
 * spell name is set to the given name. currently other languages just get
 * discarded
 */
inline void
decode_name(std::string& name,
            const TiXmlElement *const pelement)
{
  if (attribute_to_string("language", pelement) == "en")
    name = text_to_string(pelement);
}

/**
 * @brief adds the xml information to a given school class
 * @param school school class to add the information to
 * @param pelement the school entry in the xml
 *
 * reads the school information and all information from the subschools
 * and the descriptor if present.
 * Throws an Invalid_Element if one of the subelements couldn't be read
 * correctly.
 */
void
decode_school(Spell_School& school,
              const TiXmlElement *const pelement)
{
  school.set_school(attribute_to_string("type", pelement));

  const TiXmlElement* psubelement = pelement->FirstChildElement( "subschool" );
  if ( psubelement )
    do
      school.add_subschool(attribute_to_string("type", psubelement));
    while (psubelement->NextSiblingElement("subschool"));

  psubelement = pelement->FirstChildElement( "descriptor" );
  if ( psubelement )
    school.set_descriptor(attribute_to_string("type", psubelement));
}

/**
 * @brief adds the level information to a given level class
 * @param level level class to add the information to
 * @param pelement pointer to the level in the xml
 *
 * adds the given level to the given spell. This function only adds the one
 * level pelement points to and adds it to the spell. Existing levels remain
 * untouched.
 */
void
decode_level(Spell_Levels& level,
             const TiXmlElement *const pelement)
{
  std::string type;
  int value = 0;
  if ( pelement->QueryStringAttribute("type",&type) == TIXML_SUCCESS )
    {
      if ( pelement->QueryIntAttribute("value", &value) == TIXML_SUCCESS )
        level.add_level( type, value );
      else
        throw RPG::xml_error("failed to decode level value");
    }
  else
    throw RPG::xml_error("failed to decode level type");
}

/**
 * @brief adds the xml information to a given casting time class
 * @param time class to add the xml information to
 * @param pelement pointer to the casting time in the xml
 */
inline void
decode_casting_time(Spell_Casting_Time& time,
                    const TiXmlElement *const pelement)
{
  time.set(attribute_to_string("type", pelement),
           attribute_to_int("value", pelement));
}

/**
 * @brief add the component information to the given components class
 * @param pspell spell to add the information to
 * @param pelement pointer to the component in the xml
 *
 * adds the given component to the given spell. This function only decodes
 * the one given component and doesn't search for other components. In the
 * same way it only manipulates the one component setting.
 *
 * @todo add support for M/DF (with description)
 */
void
decode_component(Spell_Components& components,
                 const TiXmlElement *const pelement)
{
  std::string type = attribute_to_string("type", pelement);
  if ( type.length() == 1 )
    switch ( std::tolower(type[0]) )
      {
      case 'v':
        components.set_verbal(true);
        break;
      case 's':
        components.set_somatic(true);
        break;
      case 'm':
        components.set_material(true, text_to_string(pelement));
        break;
      case 'f':
        components.set_focus(true, text_to_string(pelement));
        break;
      default:
        throw RPG::xml_error("invalid component type: " + type);
      }
  else
    if (to_lower(type) == "df")
      components.set_divine_focus(true);
    else
      throw RPG::xml_error("invalid component type: " + type);
}

/**
 * @brief add the range information to the given spell
 * @param range range class to add the information to
 * @param pelement pointer to the range in the xml
 */
void
decode_range(Spell_Range& range,
             const TiXmlElement *const pelement)
{
  std::string type = to_lower(attribute_to_string("type", pelement));
  if (type == "personal" || type == "touch" || type == "close" ||
      type == "medium" || type == "long" || type == "unlimited")
    range.set_type(type);
  else
    range.set_type(attribute_to_string("value", pelement));
}

/**
 * @brief add the duration information to the given class
 * @param duration class to add the information to
 * @param pelement pointer to the duration in the xml
 */
void
decode_duration(Spell_Duration& duration,
                const TiXmlElement *const pelement)
{
  duration.set_dismissible(attribute_to_bool("dismissible", pelement));

  std::string type = attribute_to_string("type", pelement);
  duration.set_type(type);

  str_lower(type);
  /// @todo check if list is complete
  if ( type == "instantaneous" || type == "permanent" || type == "see text" )
    return;
  else
    duration.read_level(attribute_to_string("value", pelement));
}

/**
 * @brief function to decode a saving throw xml entry
 * @param saving_throw the saving throw to store the data in
 * @param pelement pointer to the saving throw xml entry
 * @todo add error handling
 * @todo add support for multiple types
 */
void
decode_saving_throw(Spell_Saving_Throw& saving_throw,
                    const TiXmlElement *const pelement)
{
  saving_throw.set_type(attribute_to_string("type", pelement));
  saving_throw.set_value(attribute_to_string("value", pelement));
  saving_throw.set_harmless(attribute_to_bool("harmless", pelement));
  saving_throw.set_see_text(attribute_to_bool("see_text", pelement));
  saving_throw.set_object(attribute_to_bool("object", pelement));
}

/**
 * @brief add the spell resistance information to the given spell
 * @param spell_resistance class to add the spell resistance to
 * @param pelement pointer to the resistance in the xml
 */
void
decode_spell_resistance(Spell_Spell_Resistance& spell_resistance,
                        TiXmlElement const *const pelement)
{
  spell_resistance.set_resistance(attribute_to_bool("value", pelement));
  spell_resistance.set_harmless(attribute_to_bool("harmless", pelement));
  spell_resistance.set_see_text(attribute_to_bool("see_text", pelement));
}

/**
 * @brief add the description to the given spell
 * @param description class to add the description to
 * @param pelement pointer to the description in the xml
 *
 * @todo look for a way to not copy the description (leave it in the xml)
 * @todo implement language support
 */
inline void
decode_description(std::string& description,
                   TiXmlElement const *const pelement)
{
  description = text_to_string(pelement);
}

/**
 * @brief reads the elements from the xml and copies them to the Spell
 * @param pxml the element to decode
 * @return new generated spell
 *
 * @todo add a check if all necessary elements have been found
 * @todo add missing components
 * @todo add error handling
 *
 * this function checks element by element what it is and calls the respecting
 * add functions to add them to the given spell.
 */
template <>
typename Xml_Access<Pathfinder::Spell>::value_type
Xml_Access<Pathfinder::Spell>::decode(const TiXmlElement *const pxml) const
{
  /* map for easy translation of the names to tokens */
  static std::map < std::string, Spell_Token > elements;
  if (elements.size() == 0)
    elements = generate_elements_map();

  Spell result;

  TiXmlElement const * pelement = pxml->FirstChildElement();
  while (pelement)
    {
      switch(elements[pelement->Value()])
        {
        case Spell_Token::Name:
          decode_name(result.name, pelement);
          break;
        case Spell_Token::School:
          decode_school(result.school, pelement);
          break;
        case Spell_Token::Level:
          decode_level(result.levels, pelement);
          break;
        case Spell_Token::Casting_Time:
          decode_casting_time(result.casting_time, pelement);
          break;
        case Spell_Token::Components:
          decode_component(result.components, pelement);
          break;
        case Spell_Token::Range:
          decode_range(result.range, pelement);
          break;
        case Spell_Token::Duration:
          decode_duration(result.duration, pelement);
          break;
        case Spell_Token::Saving_Throw:
          decode_saving_throw(result.saving_throw, pelement);
          break;
        case Spell_Token::Spell_Resistance:
          decode_spell_resistance(result.spell_resistance, pelement);
          break;
        case Spell_Token::Description:
          decode_description(result.description, pelement);
          break;
        default:
          throw RPG::xml_error("Unknown element " +
                               pelement->ValueStr() + " found");
        }

      pelement = pelement->NextSiblingElement();
    }

  return result;
}

  template<>
    Identifier
    Xml_Access<Pathfinder::Spell>::decode_index(const TiXmlElement *const p) const
  {
    for (const auto& elem : p)
      if (elem.Value() == index_name_)
        {
          std::string result;
          decode_name(result, &elem);
          return result;
        }
    throw xml_error("Decodation of index failed. Index " +
                    index_name_ + " not found!");
  }
