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
  //TiXmlElement* spell = spells_.find_spell( spell_name );
  Spell temp;
  return temp;
}
