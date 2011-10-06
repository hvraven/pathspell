#include "xml.h"
#include "error.h"

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

Spell_Element Spells::get_spell_spell_element_( TiXmlElement* pspell,
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
	      Spell_Element temp(type, value);
	      return temp;
	    }
	  else
	    {
	      Spell_Element temp(type);
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
  Components temp;
  return temp;
}

Saving_Throw Spells::get_spell_saving_throw_( TiXmlElement* pspell )
{
  Saving_Throw temp;
  return temp;
}

Spell_Resistance Spells::get_spell_spell_resistance_( TiXmlElement* pspell )
{
  Spell_Resistance temp;
  return temp;
}

std::string Spells::get_spell_description_( TiXmlElement* pspell )
{
  TiXmlElement* pdescription = pspell->FirstChildElement( "description" );
  return pdescription->GetText();
}

std::string Spells::get_spell_link_( TiXmlElement* pspell )
{
  TiXmlElement* plink = pspell->FirstChildElement( "link" );
  return plink->GetText();
}
