#include "xml.h"
#include "error.h"
#include "strmanip.h"

Spells::Spells( const char* filename)
  : doc_(filename),
    spells_()
{
  if ( ! doc_.LoadFile() )
    throw File_Load_Error();

  spells_.fill_list( doc_ );
}

Spells::~Spells()
{
}

Spell Spells::get_spell( const std::string& spell_name )
{
  TiXmlElement* spell = spells_.find_spell( spell_name );

  Spell temp( spell_name , get_spell_school_(spell),
	      get_spell_level_(spell), get_spell_casting_time_(spell),
	      get_spell_components_(spell), get_spell_range_(spell),
	      get_spell_duration_(spell), get_spell_saving_throw_(spell),
	      get_spell_spell_resistance_(spell),
	      get_spell_description_(spell), get_spell_link_(spell) );

  if ( check_spell_target_( spell ) )
    {
      temp.set_target( get_spell_target_( spell ) );
    }

  return temp;
}

School Spells::get_spell_school_( TiXmlElement* pspell )
{
  TiXmlElement* pschool = pspell->FirstChildElement( "school" );
  if ( pschool )
    {
      const std::string school = pschool->Attribute( "type" );

      TiXmlElement* psubschool = pschool->FirstChildElement();
      if ( psubschool )
	{
	  std::vector < std::string > subschool;
	  while ( psubschool )
	    {
	      std::string temp;
	      subschool.push_back( psubschool->Attribute( "type" ) );
	      psubschool = psubschool->NextSiblingElement();
	    }

	  School temp(school, subschool);
	  return temp;
	}
      else
	{
	  School temp(school);
	  return temp;
	}
    }
  else
    throw Missing_Element( SCHOOL );
}

Level Spells::get_spell_level_( TiXmlElement* pspell )
{

  TiXmlElement* plevel = pspell->FirstChildElement( "level" );
  if ( plevel )
    {
      Level work;

      while ( plevel )
	{
	  std::string type = plevel->Attribute( "type" );
	  int value;
	  plevel->QueryIntAttribute( "value", &value);
	  if ( type != "" )
	    {
	      if ( value )
		work.add_level( type, value );
	      else
		throw Missing_Element ( LEVEL_VALUE );
	    }
	  else
	    throw Missing_Element ( LEVEL_TYPE );

	  plevel = plevel->NextSiblingElement( "level" );
	}
      return work;
    }
  else
    throw Missing_Element ( LEVEL );
}

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
}
