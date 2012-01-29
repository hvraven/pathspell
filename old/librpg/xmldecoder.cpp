#include "xml.h"
#include "error.h"
#include "strmanip.h"

/**
 * \brief reads the elements from the xml and copies them to the Spell
 * \param pspell pointer to the spell to fill
 * \param pxml pointer to the xml where to load from
 *
 * \todo add a check if all necessary elements have been found
 * \todo change the elements map to a static version which isn't created newly
 * at every call
 * \todo add missing components
 * \todo add error handling
 * \todo change from set element to a version, where a pointer to the spell
 * element is returned (no extra element creation)
 *
 * this function checks element by element what it is and calls the respecting
 * add functions to add them to the given spell.
 */
void Spell_List::decode_elements_( Spell *const pspell,
                                   const TiXmlElement *const pxml) const
{
  /* map for easy translation of the names to tokens */
  std::map < std::string, Spell_Element_Token > elements;
  elements[ "name" ] = NAME;
  elements[ "school" ] = SCHOOL;
  elements[ "level" ] = LEVEL;
  elements[ "domain" ] = DOMAIN;
  elements[ "casting_time" ] = CASTING_TIME;
  elements[ "component" ] = COMPONENTS;
  elements[ "range" ] = RANGE;
  elements[ "duration" ] = DURATION;
  elements[ "saving_throw" ] = SAVING_THROW;
  elements[ "spell_resistance" ] = SPELL_RESISTANCE;
  elements[ "short_description" ] = SHORT_DESCRIPTION;
  elements[ "description" ] = DESCRIPTION;
  elements[ "target" ] = TARGET;
  elements[ "annotation" ] = ANNOTATION;
  elements[ "note" ] = NOTE;
  elements[ "area" ] = AREA;

  TiXmlElement const * pelement = pxml->FirstChildElement();
  while ( pelement )
    {
      switch( elements[ pelement->Value() ] )
	{
	case NAME:
	  {
	    pspell->set_name( decode_name(pelement) );
	    break;
	  }
	case SCHOOL:
	  {
	    pspell->set_school( decode_school(pelement) );
	    break;
	  }
        case LEVEL:
	  {
            Level temp = pspell->get_level();
            decode_level(temp, pelement);
	    pspell->set_level( temp );
	    break;
          }
        case CASTING_TIME:
          {
            pspell->set_casting_time( decode_casting_time(pelement) );
            break;
          }
        case COMPONENTS:
          {
            Components temp = pspell->get_components();
            decode_component(temp, pelement);
            pspell->set_components( temp );
            break;
          }
        case RANGE:
          {
            pspell->set_range( decode_range(pelement) );
            break;
          }
        case DURATION:
          {
            pspell->set_duration( decode_duration(pelement) );
            break;
          }
        case SAVING_THROW:
          {
            pspell->set_saving_throw( decode_saving_throw(pelement) );
            break;
          }
        case SPELL_RESISTANCE:
          {
            pspell->set_spell_resistance( decode_spell_resistance(pelement) );
            break;
          }
        case DESCRIPTION:
          {
            pspell->set_description( decode_description(pelement) );
            break;
          }
	default:
	  {
	    break;
	  }
	}

      pelement = pelement->NextSiblingElement();
    }
}

/**
 * \brief reads the xml information to a name class
 * \param pelement pointer to the xml name entry
 * \see decode_name( Name& name, const TiXmlElement *const pelement )
 */
Name decode_name( const TiXmlElement *const pelement )
{
  Name work;
  decode_name( work, pelement );
  return work;
}

/**
 * \brief gets the xml data of a name element and writes it to the spell
 * \param spell the spell to save the name in
 * \param pelement pointer to the xml name entry
 * \todo set a global language and use it only if language matches
 * \todo add error handling
 *
 * reads the language attribute of the spell. If the language is en the
 * spell name is set to the given name. currently other languages just get
 * discarded
 */
void decode_name( Name& name, const TiXmlElement *const pelement )
{
  std::string language;
  if ( pelement->QueryStringAttribute("language", &language) == TIXML_SUCCESS )
    if ( language == "en" )
      name.set_text( pelement->GetText() );
}

/**
 * \todo find out why we have this function and make a documentation
 */
std::vector < std::string > Spell_List::get_names_
    ( TiXmlElement const * const pspell ) const
{
  std::vector < std::string > result;

  for ( TiXmlElement const * pelement = pspell->FirstChildElement( "name" ) ;
	pelement ; pelement = pelement->NextSiblingElement( "name" ) )
    {
      result.push_back( pelement->GetText() );
    }

  return result;
}

/**
 * \brief adds the xml information to a new school class
 * \param pelement pointer to the xml school entry
 * \see decode_school( School& school, const TiXmlElement *const pelement )
 */
School decode_school( const TiXmlElement *const pelement )
{
  School work;
  decode_school( work, pelement );
  return work;
}

/**
 * \brief adds the xml information to a given school class
 * \param school school class to add the information to
 * \param pelement the school entry in the xml
 *
 * reads the school information and all information from the subschools
 * and the descriptor if present.
 * Throws an Invalid_Element if one of the subelements couldn't be read
 * correctly.
 */
void decode_school( School& school, const TiXmlElement *const pelement )
{
  std::string type;
  if ( pelement->QueryStringAttribute("type",&type) != TIXML_SUCCESS )
    throw Missing_Element(SCHOOL);
  school.set_school( type );

  const TiXmlElement* psubelement = pelement->FirstChildElement( "subschool" );
  if ( psubelement )
    do
      {
        if ( psubelement->QueryStringAttribute("type",&type)
             != TIXML_SUCCESS )
          throw Invalid_Element(SUBSCHOOL);
        school.add_subschool( type );
        psubelement = psubelement->NextSiblingElement( "subschool" );
      }
    while ( psubelement );

  psubelement = pelement->FirstChildElement( "descriptor" );
  if ( psubelement )
    {
      if ( psubelement->QueryStringAttribute("type",&type)
           != TIXML_SUCCESS )
        throw Invalid_Element(DESCRIPTOR);
      school.set_descriptor( type );
    }
}

/**
 * \brief adds the xml information to a new level class
 * \param pelement pointer to the xml level entry
 * \see decode_level( Level& level, const TiXmlElement *const pelement )
 * \note this function creates a new level class containing only the last
 * level
 */
Level decode_level( const TiXmlElement *const pelement )
{
  Level work;
  decode_level( work, pelement );
  return work;
}

/**
 * \brief adds the level information to a given level class
 * \param level level class to add the information to
 * \param pelement pointer to the level in the xml
 *
 * adds the given level to the given spell. This function only adds the one
 * level pelement points to and adds it to the spell. Existing levels remain
 * untouched.
 */
void decode_level( Level& level, const TiXmlElement *const pelement )
{
  std::string type;
  int value = 0;
  if ( pelement->QueryStringAttribute("type",&type) == TIXML_SUCCESS )
    {
      if ( pelement->QueryIntAttribute("value", &value) == TIXML_SUCCESS )
        level.add_level( type, value );
      else
        throw Missing_Element(LEVEL_VALUE);
    }
  else
    throw Missing_Element(LEVEL_TYPE);
}

/**
 * \brief adds the xml information to a new casting time class
 * \param pelement pointer to the xml casting time entry
 * \see decode_casting_time( Casting_Time&, const TiXmlElement *const )
 */
Casting_Time decode_casting_time( const TiXmlElement *const pelement )
{
  Casting_Time work;
  decode_casting_time(work, pelement);
  return work;
}

/**
 * \brief adds the xml information to a given casting time class
 * \param time class to add the xml information to
 * \param pelement pointer to the casting time in the xml
 */
void decode_casting_time( Casting_Time& time,
                          const TiXmlElement *const pelement )
{
  std::string type;
  int value = 0;
  if ( pelement->QueryStringAttribute("type", &type) == TIXML_SUCCESS )
    {
      if ( pelement->QueryIntAttribute("value", &value) == TIXML_SUCCESS )
        time.set( type, value );
      else
        throw Missing_Element(CASTING_TIME);
    }
  else
    throw Missing_Element(CASTING_TIME_TYPE);
}

/**
 * \brief adds the xml information to a new components class
 * \param pelement pointer to the xml component entry
 * \see decode_component( Components&, const TiXmlElement *const )
 */
Components decode_component( const TiXmlElement *const pelement )
{
  Components work;
  decode_component( work, pelement );
  return work;
}

/**
 * \brief add the component information to the given components class
 * \param pspell spell to add the information to
 * \param pelement pointer to the component in the xml
 *
 * adds the given component to the given spell. This function only decodes
 * the one given component and doesn't search for other components. In the
 * same way it only manipulates the one component setting.
 *
 * \todo add support for M/DF (with description)
 */
void decode_component( Components& components,
                       const TiXmlElement *const pelement )
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
            throw Invalid_Element(COMPONENTS);
          }
      else
        if ( type == "DF" )
          {
            components.set_divine_focus( true );
          }
        else
          throw Invalid_Element(COMPONENTS);
    }
  else
    throw Invalid_Element(COMPONENTS);
}

/**
 * \brief adds the xml information to a new range class
 * \param pelement pointer to the xml range entry
 * \see decode_range( Range&, const TiXmlElement *const )
 */
Range decode_range( const TiXmlElement *const pelement )
{
  Range work;
  decode_range( work, pelement );
  return work;
}

/**
 * \brief add the range information to the given spell
 * \param range range class to add the information to
 * \param pelement pointer to the range in the xml
 */
void decode_range( Range& range, const TiXmlElement *const pelement )
{
  std::string type;
  int value = 0;
  if ( pelement->QueryStringAttribute("type", &type) == TIXML_SUCCESS )
    {
      if ( type == "personal" || type == "touch" || type == "close" ||
           type == "medium" || type == "long" || type == "unlimited" )
        range.set_type(type);
      else
        {
          if ( pelement->QueryIntAttribute("value", &value) == TIXML_SUCCESS )
            range.set(type, value);
          else
            throw Invalid_Element(RANGE_VALUE);
        }
    }
  else
    throw Invalid_Element(RANGE);
}

/**
 * \brief adds the xml information to a new duration class
 * \param pelement pointer to the xml duration entry
 * \see decode_duration( Duration&, const TiXmlElement *const )
 */
Duration decode_duration( const TiXmlElement *const pelement )
{
  Duration work;
  decode_duration( work, pelement );
  return work;
}

/**
 * \brief add the duration information to the given class
 * \param duration class to add the information to
 * \param pelement pointer to the duration in the xml
 */
void decode_duration( Duration& duration,
                      const TiXmlElement *const pelement )
{
  std::string type;
  bool dismissible = false;

  if ( pelement->QueryBoolAttribute("dismissible", &dismissible)
       == TIXML_SUCCESS )
    duration.set_dismissible( dismissible );

  if ( pelement->QueryStringAttribute("type", &type) == TIXML_SUCCESS )
    {
      duration.set_type( type );
      /// \todo check if list is complete
      if ( type == "instantaneous" || type == "permanent" || type == "see text" )
        return;
      else
        {
          if ( pelement->QueryStringAttribute("value", &type) == TIXML_SUCCESS )
            duration.read_level( type );
          else
            throw Invalid_Element(DURATION);
        }
    }
  else
    throw Invalid_Element(DURATION);
}

/**
 * \brief adds the xml information to a new saving throw class
 * \param pelement pointer to the xml saving throw entry
 * \see decode_saving_throw( Saving_Throw&, const TiXmlElement *const )
 */
Saving_Throw decode_saving_throw( const TiXmlElement *const pelement )
{
  Saving_Throw result;
  decode_saving_throw( result, pelement );
  return result;
}

/**
 * \brief function to decode a saving throw xml entry
 * \param saving_throw the saving throw to store the data in
 * \param pelement pointer to the saving throw xml entry
 * \todo add error handling
 * \todo add support for multiple types
 */
void decode_saving_throw( Saving_Throw& saving_throw,
                          const TiXmlElement *const pelement )
{
  std::string type;
  if ( pelement->QueryStringAttribute("type",&type) == TIXML_SUCCESS )
    {
      std::string value;
      if ( pelement->QueryStringAttribute("value",&value)
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
 * \brief adds the xml information to a new spell resistance class
 * \param pelement pointer to the xml spell resistance entry
 * \see decode_spell_resistance( Spell_Resistance&, const TiXmlElement *const )
 */
Spell_Resistance decode_spell_resistance( const TiXmlElement *const pelement )
{
  Spell_Resistance result;
  decode_spell_resistance( result, pelement );
  return result;
}

/**
 * \brief add the spell resistance information to the given spell
 * \param spell_resistance class to add the spell resistance to
 * \param pelement pointer to the resistance in the xml
 */
void decode_spell_resistance( Spell_Resistance& spell_resistance,
                              TiXmlElement const *const pelement )
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
 * \brief adds the xml information to a new description class
 * \param pelement pointer to the xml description entry
 * \see decode_description( Description&, const TiXmlElement *const )
 */
Description decode_description( const TiXmlElement *const pelement )
{
  Description result;
  decode_description( result, pelement );
  return result;
}

/**
 * \brief add the description to the given spell
 * \param description class to add the description to
 * \param pelement pointer to the description in the xml
 *
 * \todo look for a way to not copy the description (leave it in the xml)
 * \todo implement language support
 */
void decode_description( Description& description,
                         TiXmlElement const *const pelement )
{
  description.set_text(pelement->GetText());
}
