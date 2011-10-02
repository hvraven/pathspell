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

TiXmlElement* Spell_List::find_spell( const std::string spell )
{
  return spell_list_[spell];
}

void Spell_List::fill_list ( TiXmlDocument& doc )
{
  //  const TiXmlElement* p_root = doc.FirstChildElement( "spell" );
  TiXmlHandle h_root  = &doc;
  TiXmlElement* p_root = h_root.ToElement();

  for ( ; p_root; p_root = p_root->NextSiblingElement() )
    {
      TiXmlElement* p_name = p_root->FirstChildElement( "name" );
      if ( p_name )
	{
	  std::string name = p_name->GetText();
	  spell_list_[name] = p_root;
	}
      else
	throw Missing_Element( NAME );
    }
}
