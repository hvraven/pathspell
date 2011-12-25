#include "xml.h"
#include "error.h"

/**
 * \brief creates a new spell list and loads the spells in the given file
 * \param filename filesystem path, where the xml can be found
 */
Spell_List::Spell_List( const std::string& filename )
  : doc_(filename),
    spell_list_()
{
  if ( ! doc_.LoadFile() )
    throw File_Load_Error();

  fill_list_ ( doc_ );
}

/**
 * \brief deletes all the cached spells
 */
Spell_List::~Spell_List()
{
  for ( spell_list::const_iterator it = spell_list_.begin() ;
	it != spell_list_.end() ; it++ )
      if ( it->pspell )
	delete it->pspell;
}

/**
 * \brief loads the elements from a given file
 * \param doc the file from which the data should be loaded
 */
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

/**
 * \brief returns a list of names of all spells saved in the Spell_List
 */
std::vector < std::string > Spell_List::get_spell_list()
{
  std::vector < std::string > result;

  for ( spell_name_map::const_iterator it = spell_name_map_.begin() ;
	it != spell_name_map_.end() ; it++ )
    result.push_back( it->first );

  return result;
}

/**
 * \brief returns a ref to a spell
 * \param spell a name of the spell
 */
Spell& Spell_List::get_spell( const std::string& spell )
{
  spell_list_iterator ittag = spell_list_.begin()
    + spell_name_map_[ spell ];
  check_spell_( ittag );
  return *( ittag->pspell );
}

/**
 * \brief returns a ref to a spell with the gurantee it is valid
 */
Spell& Spell_List::get_checked_spell_ref_( const unsigned int spell )
{
  spell_list_iterator ittag = spell_list_.begin() + spell;
  check_spell_( ittag );
  return *( ittag->pspell );
}

/**
 * \brief returns a spell pointer with the guarantee it is valid
 */
Spell* Spell_List::get_checked_spell_pointer_( const unsigned int spell )
{
  spell_list_iterator ittag = spell_list_.begin() + spell;
  check_spell_( ittag );
  return ittag->pspell;
}

/**
 * \brief loads uncached spell
 *
 * checks if the spells cache if valid. If not it loads the data
 * and creates a new spell if needed.
 * \param ittag the spell to check and load
 */
void Spell_List::check_spell_( spell_list_iterator ittag)
{
  if ( ! ittag->cache_valid )
    {
      if ( ! ittag->pspell )
	ittag->pspell = new Spell();
      decode_elements_( ittag->pspell, ittag->pxml );
      ittag->cache_valid = true;
    }
}
