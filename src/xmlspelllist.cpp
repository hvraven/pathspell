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
  for ( spell_list::const_iterator it = spell_list_.begin() ;
	it != spell_list_.end() ; it++ )
      if ( it->pspell )
	delete it->pspell;
}

/*TiXmlElement* Spell_List::find_spell( const std::string& spell )
{
  return spell_list_[spell].pxml;
  }*/

void Spell_List::fill_list_ ( TiXmlDocument& doc )
{
  TiXmlHandle hroot  = &doc;
  for ( TiXmlElement const * pspell
	  = hroot.FirstChildElement().FirstChild().ToElement() ;
	pspell ; pspell = pspell->NextSiblingElement() )
    {
      spell_list_.push_back( Spell_Tag( pspell ) );
      const unsigned int position = spell_list_.size() - 1;

      std::vector < std::string > names = get_names_( pspell );

      for ( std::vector<std::string>::const_iterator itnames = names.begin() ;
	    itnames != names.end() ; itnames++ )
	spell_name_map_[ *itnames ] = position;
    }
}

std::vector < std::string > Spell_List::get_spell_list()
{
  std::vector < std::string > result;

  for ( spell_name_map::const_iterator it = spell_name_map_.begin() ;
	it != spell_name_map_.end() ; it++ )
    result.push_back( it->first );

  return result;
}

Spell& Spell_List::get_spell( const std::string& spell )
{
  spell_list_iterator ittag = spell_list_.begin()
    + spell_name_map_[ spell ];
  if ( ittag->cache_valid )
    {
      return *( ittag->pspell );
    }
  else
    {
      read_spell_(ittag);
      return *(ittag->pspell);
    }
}

void Spell_List::read_spell_( spell_list_iterator ittag)
{
  if ( ! ittag->pspell )
    ittag->pspell = new Spell();
  add_elements_( ittag->pspell, ittag->pxml );
  ittag->cache_valid = true;
}
