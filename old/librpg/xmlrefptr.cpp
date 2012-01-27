#include "xml.h"
#include "error.h"

Spell_RefPtr::Spell_RefPtr( Spell_List * const plist,
			    const unsigned int spell )
  : plist_(plist),
    spell_(spell)
{
  if ( ! plist_ )
    throw Invalid_Pointer();
}

Spell_RefPtr::Spell_RefPtr( Spell_List * const plist,
			    const std::string& spell )
  : plist_(plist)
{
  if ( plist_ )
    spell_ = plist_->find_spell_ ( spell );
  else
    throw Invalid_Pointer();
}
