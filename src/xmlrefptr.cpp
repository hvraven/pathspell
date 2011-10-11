#include "xml.h"

Spell_RefPtr::Spell_RefPtr( Spell_List const * const plist,
			    Spell_Tag const * const ptag )
  : pspell_(),
    plist_(plist),
    ptag_(ptag)
{
}

Spell_RefPtr::Spell_RefPtr( Spell_List const * const plist,
			    const std::string& name )
  : pspell_( plist->get_spell_element(name) ),
    plist_(plist),
    ptag_(0)
{
  const Spell_Tag* ptag = plist->get_tag_pointer_( name );
  ptag_ = ptag;
}

Spell& Spell_RefPtr::operator*()
{
  if ( ptag_->pspell )
    return *(ptag_->pspell);
  else
    {
      plist_->loadspell( ptag_ );
      return *(ptag_->pspell);
    }
}

Spell* Spell_RefPtr::operator->()
{
  if ( ptag_->pspell )
    return ptag_->pspell;
  else
    {
      plist_->loadspell( ptag_ );
      return ptag_->pspell;
    }
}
