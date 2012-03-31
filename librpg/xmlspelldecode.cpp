#include <map>
#include "error.h"
#include "strmanip.h"
#include "xmlspell.h"

using namespace RPG::Pathfinder;

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
Spell
Xml_Spell_List::decode(const TiXmlElement *const pxml) const
{
  /* map for easy translation of the names to tokens */
  static std::map < std::string, Spell_Token > elements;
  if (elements.size() == 0)
    {
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
    }

  Spell result;

  TiXmlElement const * pelement = pxml->FirstChildElement();
  while ( pelement )
    {
      switch( elements[ pelement->Value() ] )
        {
        case Spell_Token::Name:
          result.set_name( decode_name(pelement) );
          break;
        case Spell_Token::School:
          result.set_school( decode_school(pelement) );
          break;
        case Spell_Token::Level:
          {
            Spell_Level temp = result.get_level();
            decode_level(temp, pelement);
            result.set_levels( temp );
            break;
          }
        case Spell_Token::Casting_Time:
          result.set_casting_time( decode_casting_time(pelement) );
          break;
        case Spell_Token::Components:
          decode_component(result.get_components(), pelement);
          break;
        case Spell_Token::Range:
          result.set_range( decode_range(pelement) );
          break;
        case Spell_Token::Duration:
          result.set_duration( decode_duration(pelement) );
          break;
        case Spell_Token::Saving_Throw:
          result.set_saving_throw( decode_saving_throw(pelement) );
          break;
        case Spell_Token::Spell_Resistance:
          result.set_spell_resistance( decode_spell_resistance(pelement) );
          break;
        case Spell_Token::Description:
          result.set_description( decode_description(pelement) );
          break;
        default:
          break;
        }

      pelement = pelement->NextSiblingElement();
    }

  return result;
}

/**
 * @brief reads the xml information to a name class
 * @param pelement pointer to the xml name entry
 * @see decode_name( Name& name, const TiXmlElement *const pelement )
 */
std::string
Xml_Spell_List::decode_name(const TiXmlElement *const pelement) const
{
  std::string work;
  decode_name(work, pelement);
  return work;
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
void
Xml_Spell_List::decode_name(std::string& name,
                            const TiXmlElement *const pelement) const
{
  std::string language;
  if (((pelement->QueryStringAttribute("language", &language)) == TIXML_SUCCESS))
    if (language == "en")
      name = pelement->GetText();
}

/**
 * @brief adds the xml information to a new school class
 * @param pelement pointer to the xml school entry
 * @see decode_school( School& school, const TiXmlElement *const pelement )
 */
Spell_School
Xml_Spell_List::decode_school(const TiXmlElement *const pelement) const
{
  Spell_School work;
  decode_school( work, pelement );
  return work;
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
Xml_Spell_List::decode_school(Spell_School& school,
                              const TiXmlElement *const pelement) const
{
  std::string type;
  if ( pelement->QueryStringAttribute("type",&type) != TIXML_SUCCESS )
    throw RPG::xml_error("decoding of school type failed");
  school.set_school( type );

  const TiXmlElement* psubelement = pelement->FirstChildElement( "subschool" );
  if ( psubelement )
    do
      {
        if (psubelement->QueryStringAttribute("type",&type)
            != TIXML_SUCCESS)
          throw RPG::xml_error("decoding of school subelement type failed");
        school.add_subschool( type );
        psubelement = psubelement->NextSiblingElement( "subschool" );
      }
    while ( psubelement );

  psubelement = pelement->FirstChildElement( "descriptor" );
  if ( psubelement )
    {
      if (psubelement->QueryStringAttribute("type",&type)
          != TIXML_SUCCESS)
        throw RPG::xml_error("decoding of school descriptor type failed");
      school.set_descriptor( type );
    }
}

/**
 * @brief adds the xml information to a new level class
 * @param pelement pointer to the xml level entry
 * @see decode_level( Level& level, const TiXmlElement *const pelement )
 * @note this function creates a new level class containing only the last
 * level
 */
Spell_Level
Xml_Spell_List::decode_level(const TiXmlElement *const pelement) const
{
  Spell_Level work;
  decode_level( work, pelement );
  return work;
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
Xml_Spell_List::decode_level(Spell_Level& level,
                             const TiXmlElement *const pelement) const
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
 * @brief adds the xml information to a new casting time class
 * @param pelement pointer to the xml casting time entry
 * @see decode_casting_time( Casting_Time&, const TiXmlElement *const )
 */
Spell_Casting_Time
Xml_Spell_List::decode_casting_time(const TiXmlElement *const pelement) const
{
  Spell_Casting_Time work;
  decode_casting_time(work, pelement);
  return work;
}

/**
 * @brief adds the xml information to a given casting time class
 * @param time class to add the xml information to
 * @param pelement pointer to the casting time in the xml
 */
void
Xml_Spell_List::decode_casting_time(Spell_Casting_Time& time,
                                    const TiXmlElement *const pelement) const
{
  std::string type;
  int value = 0;
  if ( pelement->QueryStringAttribute("type", &type) == TIXML_SUCCESS )
    {
      if ( pelement->QueryIntAttribute("value", &value) == TIXML_SUCCESS )
        time.set( type, value );
      else
        throw RPG::xml_error("failed to decode casting time value");
    }
  else
    throw RPG::xml_error("failed to decode casting time type");
}

/**
 * @brief adds the xml information to a new components class
 * @param pelement pointer to the xml component entry
 * @see decode_component( Components&, const TiXmlElement *const )
 */
Spell_Components
Xml_Spell_List::decode_component(const TiXmlElement *const pelement) const
{
  Spell_Components work;
  decode_component( work, pelement );
  return work;
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
Xml_Spell_List::decode_component(Spell_Components& components,
                                 const TiXmlElement *const pelement) const
{
  std::string type;
  if ( pelement->QueryStringAttribute("type", &type) == TIXML_SUCCESS )
    {
      if ( type.length() == 1 )
        switch ( type[0] )
          {
          case 'V':
            {
              components.set_verbal(true);
              break;
            }
          case 'S':
            {
              components.set_somatic(true);
              break;
            }
          case 'M':
            {
              components.set_material(true, pelement->GetText() );
              break;
            }
          case 'F':
            {
              components.set_focus(true, pelement->GetText() );
              break;
            }
          default:
            throw RPG::xml_error("invalid component type: " + type);
          }
      else
        if ( type == "DF" )
          {
            components.set_divine_focus( true );
          }
        else
          throw RPG::xml_error("invalid component type: " + type);
    }
  else
    throw RPG::xml_error("failed to decode component type");
}

/**
 * @brief adds the xml information to a new range class
 * @param pelement pointer to the xml range entry
 * @see decode_range( Range&, const TiXmlElement *const )
 */
Spell_Range
Xml_Spell_List::decode_range(const TiXmlElement *const pelement) const
{
  Spell_Range work;
  decode_range( work, pelement );
  return work;
}

/**
 * @brief add the range information to the given spell
 * @param range range class to add the information to
 * @param pelement pointer to the range in the xml
 */
void
Xml_Spell_List::decode_range(Spell_Range& range,
                             const TiXmlElement *const pelement) const
{
  std::string type;
  int value = 0;
  if (pelement->QueryStringAttribute("type", &type) == TIXML_SUCCESS)
    {
      if (type == "personal" || type == "touch" || type == "close" ||
          type == "medium" || type == "long" || type == "unlimited")
        range.set_type(type);
      else
        {
          if ( pelement->QueryIntAttribute("value", &value) == TIXML_SUCCESS )
            range.set(type, value);
          else
            throw RPG::xml_error("failed to decode range value");
        }
    }
  else
    throw RPG::xml_error("failed to decode range type");
}

/**
 * @brief adds the xml information to a new duration class
 * @param pelement pointer to the xml duration entry
 * @see decode_duration( Duration&, const TiXmlElement *const )
 */
Spell_Duration
Xml_Spell_List::decode_duration(const TiXmlElement *const pelement) const
{
  Spell_Duration work;
  decode_duration( work, pelement );
  return work;
}

/**
 * @brief add the duration information to the given class
 * @param duration class to add the information to
 * @param pelement pointer to the duration in the xml
 */
void
Xml_Spell_List::decode_duration(Spell_Duration& duration,
                                const TiXmlElement *const pelement) const
{
  std::string type;
  bool dismissible = false;

  if (pelement->QueryBoolAttribute("dismissible", &dismissible)
      == TIXML_SUCCESS)
    duration.set_dismissible( dismissible );

  if (pelement->QueryStringAttribute("type", &type) == TIXML_SUCCESS)
    {
      duration.set_type( type );
      /// @todo check if list is complete
      if ( type == "instantaneous" || type == "permanent" || type == "see text" )
        return;
      else
        {
          if ( pelement->QueryStringAttribute("value", &type) == TIXML_SUCCESS )
            duration.read_level( type );
          else
            throw RPG::xml_error("failed to decode duration value");
        }
    }
  else
    throw RPG::xml_error("failed to decode duration type");
}

/**
 * @brief adds the xml information to a new saving throw class
 * @param pelement pointer to the xml saving throw entry
 * @see decode_saving_throw( Saving_Throw&, const TiXmlElement *const )
 */
Spell_Saving_Throw
Xml_Spell_List::decode_saving_throw(const TiXmlElement *const pelement) const
{
  Spell_Saving_Throw result;
  decode_saving_throw( result, pelement );
  return result;
}

/**
 * @brief function to decode a saving throw xml entry
 * @param saving_throw the saving throw to store the data in
 * @param pelement pointer to the saving throw xml entry
 * @todo add error handling
 * @todo add support for multiple types
 */
void
Xml_Spell_List::decode_saving_throw(Spell_Saving_Throw& saving_throw,
                                    const TiXmlElement *const pelement) const
{
  std::string type;
  if ( pelement->QueryStringAttribute("type",&type) == TIXML_SUCCESS )
    {
      std::string value;
      if (pelement->QueryStringAttribute("value",&value)
          == TIXML_SUCCESS)
        {
          saving_throw.set_type( type );
          saving_throw.set_value( value );

          bool temp = false;
          if ( (pelement->QueryBoolAttribute("harmless",&temp)
                == TIXML_SUCCESS) && temp )
            saving_throw.set_harmless(temp);
          temp = false;
          if ( (pelement->QueryBoolAttribute("see_text",&temp)
                == TIXML_SUCCESS) && temp )
            saving_throw.set_see_text(temp);
          temp = false;
          if ( (pelement->QueryBoolAttribute("object",&temp)
                == TIXML_SUCCESS) && temp )
            saving_throw.set_object(temp);
        }
    }
}

/**
 * @brief adds the xml information to a new spell resistance class
 * @param pelement pointer to the xml spell resistance entry
 * @see decode_spell_resistance( Spell_Resistance&, const TiXmlElement *const )
 */
Spell_Spell_Resistance
Xml_Spell_List::decode_spell_resistance
    (const TiXmlElement *const pelement) const
{
  Spell_Spell_Resistance result;
  decode_spell_resistance( result, pelement );
  return result;
}

/**
 * @brief add the spell resistance information to the given spell
 * @param spell_resistance class to add the spell resistance to
 * @param pelement pointer to the resistance in the xml
 */
void
Xml_Spell_List::decode_spell_resistance
    (Spell_Spell_Resistance& spell_resistance,
     TiXmlElement const *const pelement) const
{
  bool temp = false;

  if ( (pelement->QueryBoolAttribute("harmless",&temp)
        == TIXML_SUCCESS) && temp )
    spell_resistance.set_harmless(true);
  if ( (pelement->QueryBoolAttribute("see_text",&temp)
        == TIXML_SUCCESS) && temp )
    spell_resistance.set_see_text(true);
  if ( (pelement->QueryBoolAttribute("value",&temp)
        == TIXML_SUCCESS) && temp )
    spell_resistance.set_resistance(true);
}

/**
 * @brief adds the xml information to a new description class
 * @param pelement pointer to the xml description entry
 * @see decode_description( Description&, const TiXmlElement *const )
 */
std::string
Xml_Spell_List::decode_description(const TiXmlElement *const pelement) const
{
  std::string result;
  decode_description( result, pelement );
  return result;
}

/**
 * @brief add the description to the given spell
 * @param description class to add the description to
 * @param pelement pointer to the description in the xml
 *
 * @todo look for a way to not copy the description (leave it in the xml)
 * @todo implement language support
 */
void
Xml_Spell_List::decode_description(std::string& description,
                                   TiXmlElement const *const pelement) const
{
  description = pelement->GetText();
}
