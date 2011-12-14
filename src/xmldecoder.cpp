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
 *
 * this function checks element by element what it is and calls the respecting
 * add functions to add them to the given spell.
 */
void Spell_List::decode_elements_( Spell* const pspell,
                                   TiXmlElement const * const pxml)
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
	    decode_name_( pspell, pelement );
	    break;
	  }
	case SCHOOL:
	  {
	    decode_school_( pspell, pelement );
	    break;
	  }
        case LEVEL:
	  {
	    decode_level_( pspell, pelement );
	    break;
          }
        case CASTING_TIME:
          {
            decode_casting_time_( pspell, pelement );
            break;
          }
        case COMPONENTS:
          {
            decode_component_( pspell, pelement );
            break;
          }
        case RANGE:
          {
            decode_range_( pspell, pelement );
            break;
          }
        case DURATION:
          {
            decode_duration_( pspell, pelement );
            break;
          }
        case SAVING_THROW:
          {
            decode_saving_throw_( pspell, pelement );
            break;
          }
        case SPELL_RESISTANCE:
          {
            decode_spell_resistance_( pspell, pelement );
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
 * \brief gets the xml data of a name element and writes it to the spell
 * \param spell the spell to save the name in
 * \param pelement pointer to the name entry
 * \todo set a global language and use it only if language matches
 *
 * reads the language attribute of the spell. If the language is en the
 * spell name is set to the given name. currently other languages just get
 * discarded
 */
void Spell_List::decode_name_( Spell* const pspell,
                               TiXmlElement const * const pelement )
{
  std::string language;
  if ( pelement->QueryStringAttribute("language", &language) == TIXML_SUCCESS )
    {
      if ( language == "en" )
        pspell->set_name( pelement->GetText() );
      /// \todo adding support for diffrent languages
    }
}

/**
 * \todo find out why we have this function and make a documentation
 */
std::vector < std::string > Spell_List::get_names_
    ( TiXmlElement const * const pspell )
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
 * \brief adds the school information from the xml to the spell
 * \param pspell spell to add the information to
 * \param pelement the school entry in the xml
 *
 * reads the school information and all information from the subschools
 * and the descriptor if present.
 * Throws an Invalid_Element if one of the subelements couldn't be read
 * correctly.
 */
void Spell_List::decode_school_( Spell* const pspell,
                                 TiXmlElement const * const pelement )
{
  std::string type;
  if ( pelement->QueryStringAttribute("type",&type) != TIXML_SUCCESS )
    throw Missing_Element(SCHOOL);
  School temp( type );

  const TiXmlElement* psubelement = pelement->FirstChildElement( "subschool" );
  if ( psubelement )
    do
      {
        if ( psubelement->QueryStringAttribute("type",&type)
             != TIXML_SUCCESS )
          throw Invalid_Element(SUBSCHOOL);
        temp.add_subschool( type );
        psubelement = psubelement->NextSiblingElement( "subschool" );
      }
    while ( psubelement );

  psubelement = pelement->FirstChildElement( "descriptor" );
  if ( psubelement )
    {
      if ( psubelement->QueryStringAttribute("type",&type)
           != TIXML_SUCCESS )
        throw Invalid_Element(DESCRIPTOR);
      temp.set_descriptor( type );
    }

  pspell->set_school( temp );
}

/**
 * \brief add the level information to the given spell
 * \param pspell spell to add the information to
 * \param pelement pointer to the level in the xml
 *
 * adds the given level to the given spell. This function only adds the one
 * level pelement points to and adds it to the spell. Existing levels remain
 * untouched.
 */
void Spell_List::decode_level_( Spell *const pspell,
                                TiXmlElement const *const pelement )
{
  std::string type;
  int value = 0;
  if ( pelement->QueryStringAttribute("type",&type) == TIXML_SUCCESS )
    {
      if ( pelement->QueryIntAttribute("value", &value) == TIXML_SUCCESS )
        pspell->add_level( type, value );
      else
        throw Missing_Element(LEVEL_VALUE);
    }
  else
    throw Missing_Element(LEVEL_TYPE);
}

/**
 * \brief add the casting time information to the given spell
 * \param pspell spell to add the information to
 * \param pelement pointer to the casting time in the xml
 */
void Spell_List::decode_casting_time_( Spell *const pspell,
                                       TiXmlElement const *const pelement )
{
  std::string type;
  int value = 0;
  if ( pelement->QueryStringAttribute("type", &type) == TIXML_SUCCESS )
    {
      if ( pelement->QueryIntAttribute("value", &value) == TIXML_SUCCESS )
        pspell->set_casting_time( Spell_Base_Element( type, value ) );
      else
        throw Missing_Element(CASTING_TIME);
    }
  else
    throw Missing_Element(CASTING_TIME_TYPE);
}

/**
 * \brief add the component information to the given spell
 * \param pspell spell to add the information to
 * \param pelement pointer to the component in the xml
 *
 * adds the given component to the given spell. This function only decodes
 * the one given component and doesn't search for other components. In the
 * same way it only manipulates the one component setting.
 */
void Spell_List::decode_component_( Spell *const pspell,
                                    TiXmlElement const *const pelement )
{
  std::string type;
  if ( pelement->QueryStringAttribute("type", &type) == TIXML_SUCCESS )
    {
      if ( type.length() == 1 )
        switch ( type[0] )
          {
          case 'V':
            {
              pspell->set_component_verbal(true);
              break;
            }
          case 'S':
            {
              pspell->set_component_somatic(true);
              break;
            }
          case 'M':
            {
              pspell->set_component_material(true, pelement->GetText() );
              break;
            }
          case 'F':
            {
              pspell->set_component_material(true, pelement->GetText() );
              break;
            }
          default:
            throw Invalid_Element(COMPONENTS);
          }
      else
        if ( type == "DF" )
          {
            pspell->set_component_divine_focus( true );
          }
        else
          throw Invalid_Element(COMPONENTS);
    }
  else
    throw Invalid_Element(COMPONENTS);
}

/**
 * \brief add the range information to the given spell
 * \param pspell spell to add the information to
 * \param pelement pointer to the range in the xml
 */
void Spell_List::decode_range_( Spell *const pspell,
                                TiXmlElement const *const pelement )
{
  std::string type;
  int value = 0;
  if ( pelement->QueryStringAttribute("type", &type) == TIXML_SUCCESS )
    {
      if ( type == "personal" || type == "touch" || type == "close" ||
           type == "medium" || type == "long" || type == "unlimited" )
        pspell->set_range( type );
      else
        {
          if ( pelement->QueryIntAttribute("value", &value) == TIXML_SUCCESS )
            pspell->set_range( Spell_Base_Element(type, value) );
          else
            throw Invalid_Element(RANGE_VALUE);
        }
    }
  else
    throw Invalid_Element(RANGE);
}

/**
 * \brief add the duration information to the given spell
 * \param pspell spell to add the information to
 * \param pelement pointer to the duration in the xml
 */
void Spell_List::decode_duration_( Spell *const pspell,
                                   TiXmlElement const *const pelement )
{
  std::string type;
  bool dismissible = false;
  Duration work;

  if ( pelement->QueryBoolAttribute("dismissible", &dismissible)
       == TIXML_SUCCESS )
    work.set_dismissible( dismissible );

  if ( pelement->QueryStringAttribute("type", &type) == TIXML_SUCCESS )
    {
      work.set_type( type );
      /// \todo check if list is complete
      if ( type == "instantaneous" || type == "permanent" || type == "see text" )
          pspell->set_duration( work );
      else
        {
          if ( pelement->QueryStringAttribute("value", &type) == TIXML_SUCCESS )
            {
              work.read_level( type );
              pspell->set_duration( work );
            }
          else
            throw Invalid_Element(DURATION);
        }
    }
  else
    throw Invalid_Element(DURATION);
}

/**
 * \brief add the saving throw information to the given spell
 * \param pspell spell to add the information to
 * \param pelement pointer to the saving throw in the xml
 */
void Spell_List::decode_saving_throw_( Spell *const pspell,
                                       TiXmlElement const *const pelement )
{
  std::string type;
  if ( pelement->QueryStringAttribute("type",&type) == TIXML_SUCCESS )
    {
      std::string value;
      if ( pelement->QueryStringAttribute("value",&value)
           == TIXML_SUCCESS)
        {
          Saving_Throw work;
          work.set_type( type );
          work.set_value( value );

          bool temp = false;
          if ( (pelement->QueryBoolAttribute("harmless",&temp)
                == TIXML_SUCCESS) && temp ) work.set_harmless(temp);
          temp = false;
          if ( (pelement->QueryBoolAttribute("see_text",&temp)
                == TIXML_SUCCESS) && temp ) work.set_see_text(temp);
          temp = false;
          if ( (pelement->QueryBoolAttribute("object",&temp)
                == TIXML_SUCCESS) && temp ) work.set_object(temp);

          pspell->set_saving_throw(work);
        }
    }
}

void Spell_List::decode_spell_resistance_( Spell *const pspell,
                                           TiXmlElement const *const pelement )
{
  bool temp = false;
  Spell_Resistance work;

  if ( (pelement->QueryBoolAttribute("harmless",&temp)
        == TIXML_SUCCESS) && temp ) work.set_harmless(true);
  if ( (pelement->QueryBoolAttribute("see_text",&temp)
        == TIXML_SUCCESS) && temp ) work.set_see_text(true);
  if ( (pelement->QueryBoolAttribute("value",&temp)
        == TIXML_SUCCESS) && temp ) work.set_resistance(true);
  pspell->set_spell_resistance(work);
}

/*
Spell_Base_Element Spells::get_spell_spell_element_( TiXmlElement* pspell,
						const std::string& search_for )
{
  TiXmlElement* pchild = pspell->FirstChildElement( search_for );
  if ( pchild )
    {
      std::string type = pchild->Attribute( "type" );
      if ( type != "" )
	{
	  int value = 0;
	  pchild->QueryIntAttribute( "value", &value );
	  if ( value )
	    {
	      Spell_Base_Element temp(type, value);
	      return temp;
	    }
	  else
	    {
	      Spell_Base_Element temp(type);
	      return temp;
	    }
	}
      else
	throw Missing_Element ( CASTING_TIME_TYPE );
    }
  else
    throw Missing_Element ( CASTING_TIME );
}

Components Spells::get_spell_components_( TiXmlElement* pspell )
{
  TiXmlElement* pcomponent = pspell->FirstChildElement( "component" );
  if ( pcomponent )
    {
      Components temp;
      while ( pcomponent )
	{
	  std::string work = pcomponent->Attribute( "type" );
	  switch ( work[0] )
	    {
	    case 'V':
	      {
		temp.set_verbal( true );
		break;
	      }
	    case 'S':
	      {
		temp.set_somatic( true );
		break;
	      }
	    case 'M':
	      {
		std::string description = pcomponent->GetText();
		temp.set_material( true, description );
		break;
	      }
	    case 'F':
	      {
		std::string description = pcomponent->GetText();
		temp.set_focus( true, description);
		break;
	      }
	    case 'D':
	      {
		if ( work[1] == 'F' )
		  {
		    temp.set_divine_focus( true );
		    break;
		  }
	      }
	    default:
	      throw Invalid_Argument();
	    }
	  pcomponent = pcomponent->NextSiblingElement( "component" );
	}
      return temp;
    }
  else
    throw Missing_Element ( COMPONENTS );
}

Saving_Throw Spells::get_spell_saving_throw_( TiXmlElement* pspell )
{
  TiXmlElement* psave = pspell->FirstChildElement( "saving_throw" );

  if ( psave )
    {
      Saving_Throw temp;
      TiXmlAttribute* pattr = psave->FirstAttribute();

      while ( pattr )
	{
	  std::string work = pattr->Name();
	  if ( work == "type" )
	    temp.set_type( pattr->ValueStr() );
	  else if ( work == "value" )
	    temp.set_value( pattr->ValueStr() );
	  else if ( work == "see_text" )
	    {
	      if ( pattr->ValueStr() == "yes" )
		temp.set_see_text( true );
	    }
	  else if ( work == "harmless" )
	    {
	      if ( pattr->ValueStr() == "yes" )
		temp.set_harmless( true );
	    }
	  pattr = pattr->Next();
	}

      return temp;
    }
  else
    throw Missing_Element( SAVING_THROW );
}

Spell_Resistance Spells::get_spell_spell_resistance_( TiXmlElement* pspell )
{
  TiXmlElement* presist = pspell->FirstChildElement( "spell_resistance" );
  Spell_Resistance temp;
  if ( presist )
    {
      TiXmlAttribute* pattr = presist->FirstAttribute();
      Spell_Resistance result;

      while ( pattr )
	{
	  std::string work = pattr->Name();

	  if ( work == "value" )
	    {
	      if ( pattr->ValueStr() == "yes" )
		result.set_resistance( true );
	      else
		if ( pattr->ValueStr() == "no" )
		  result.set_resistance( false );
		else
		  throw Invalid_Argument();
	    }
	  else if ( work == "see_text")
	    {
	      if ( pattr->ValueStr() == "yes" )
		result.set_see_text( true );
	      else
		if ( pattr->ValueStr() == "no" )
		  result.set_see_text( false );
		else
		  throw Invalid_Argument();
	    }
	  else if ( work == "harmless" )
	    {
	      if ( pattr->ValueStr() == "yes" )
		result.set_harmless( true );
	      else
		if ( pattr->ValueStr() == "no" )
		  result.set_harmless (false);
		else
		  throw Invalid_Argument();
	    }
	  pattr = pattr->Next();
	}
      return result;
    }
  else
    throw Missing_Element( SPELL_RESISTANCE );
}

std::string Spells::get_spell_description_( TiXmlElement* pspell )
{
  TiXmlElement* pdescription = pspell->FirstChildElement( "description" );
  return pdescription->GetText();
}

std::string Spells::get_spell_link_( TiXmlElement* pspell )
{
  std::string result = pspell->Attribute( "src" );
  return "";
}

bool Spells::check_spell_target_( TiXmlElement* pspell )
{
  return pspell->FirstChildElement( "target" );
}

Target* Spells::get_spell_target_( TiXmlElement* pspell )
{
  TiXmlElement* ptarget = pspell->FirstChildElement( "target" );
  if ( ptarget )
    {
      std::string type = to_lower( ptarget->Attribute( "type" ) );
      if ( type == "you" )
	{
	  Target* temp = new Target(YOU);
	  return temp;
	}
      else if ( type == "special" )
	{
	  Target* temp = new Target(SPECIAL);
	  temp->set_special( ptarget->Value() );
	  return temp;
	}
      else
	{
	  Target* temp = new Target;
	  if ( type == "creature" )
	    temp->set_type( CREATURE );
	  else if ( type == "living creature" )
	    temp->set_type( LIVING_CREATURE );
	  else if ( type == "object" )
	    temp->set_type ( OBJECT );
	  else
	    throw Invalid_Argument();

	  TiXmlAttribute* pattr = ptarget->FirstAttribute();

	  while ( pattr )
	    {
	      std::string work = pattr->Name();
	      if ( work == "distance" )
		temp->set_distance( pattr->ValueStr() );
	      else if ( work == "max_between" )
		temp->set_max_between( pattr->IntValue() );
	      else if ( work == "amount" )
		temp->set_amount( pattr->ValueStr() );
	      else if ( work != "type")
		throw Invalid_Attribute();

	      pattr = pattr->Next();
	    }
	  return temp;
	}
    }
  else
    throw Missing_Element( TARGET );
}*/
