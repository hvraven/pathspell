#include "xml.h"
#include "error.h"

Spell_List::Spell_List()
  : spell_list_()
{
}

Spell_List::Spell_List( TiXmlDocument& doc )
  : spell_list_()
{
  fill_list ( doc );
}

Spell_List::~Spell_List()
{
}

TiXmlElement* Spell_List::find_spell( const std::string& spell )
{
  return spell_list_[spell];
}

void Spell_List::fill_list ( TiXmlDocument& doc )
{
  TiXmlHandle h_root  = &doc;
  TiXmlElement* p_spell= h_root.FirstChildElement().FirstChild().ToElement();
  for ( ; p_spell; p_spell = p_spell->NextSiblingElement() )
    {
      TiXmlElement* p_name = p_spell->FirstChildElement( "name" );
      if ( p_name )
	{
	  std::string name = p_name->GetText();
	  spell_list_[name] = p_spell;
	}
      else
	throw Missing_Element( NAME );
    }
}

// TODO integrate support for multiple languages
std::vector < std::string > Spell_List::get_spell_list()
{
  std::map < std::string, TiXmlElement* >::const_iterator it =
    spell_list_.begin();

  std::vector < std::string > result;

  for ( ; it != spell_list_.end() ; it++ )
    {
      TiXmlElement* p_name = it->second->FirstChildElement( "name" );
      result.push_back( (*p_name).GetText() );
    }
  return result;
}
