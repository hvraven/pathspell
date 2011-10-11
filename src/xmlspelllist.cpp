#include "xml.h"
#include "error.h"

Spell_List::Spell_List( const std::string& filename )
  : doc_(filename),
    spell_list_()
{
  if ( ! doc_.LoadFile() )
    throw File_Load_Error();

  fill_list_ ( doc_ );
}

Spell_List::~Spell_List()
{
  for ( spell_map::const_iterator it = spell_list_.begin() ;
	it != spell_list_.end() ; it++ )
      if ( it->second.pspell )
	delete it->second.pspell;
}

/*TiXmlElement* Spell_List::find_spell( const std::string& spell )
{
  return spell_list_[spell].pxml;
  }*/

void Spell_List::fill_list_ ( TiXmlDocument& doc )
{
  TiXmlHandle h_root  = &doc;
  TiXmlElement* p_spell= h_root.FirstChildElement().FirstChild().ToElement();
  for ( ; p_spell; p_spell = p_spell->NextSiblingElement() )
    {
      TiXmlElement* p_name = p_spell->FirstChildElement( "name" );
      if ( p_name )
	{
	  std::string name = p_name->GetText();
	  spell_list_[name].pxml = p_spell;
	}
      else
	throw Missing_Element( NAME );
   }
}

std::vector < std::string > Spell_List::get_spell_list()
{
  spell_map::const_iterator it = spell_list_.begin();

  std::vector < std::string > result;

  for ( ; it != spell_list_.end() ; it++ )
    result.push_back( it->first );

  return result;
}

Spell& Spell_List::get_spell( const std::string& spell )
{
  Spell_Tag* ptag = &spell_list_[ spell ];
  if ( (*ptag).cache_valid )
    {
      return *((*ptag).pspell);
    }
  else
    {
      read_spell_(ptag);
      return *((*ptag).pspell);
    }
}

void Spell_List::read_spell_( Spell_Tag* ptag)
{
  Spell* pspell = (*ptag).pspell;
  if ( ! pspell )
    pspell = new Spell;

  add_elements_( pspell, (*ptag).pxml );
}



