#include "xml.h"
#include "error.h"

Spells::Spells( const char* filename)
  : doc_(filename),
    spells_()
{
  if ( ! doc_.LoadFile() )
    throw File_Not_Found();

  spells_.fill_list( doc_ );
}

Spells::~Spells()
{
}
/* unfinished function
Spell Spells::get_spell( const std::string spell_name )
{
  TiXmlHandle spell = spells_.find_spell( spell_name );
 }
*/
