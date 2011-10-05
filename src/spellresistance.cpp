#include "spell.h"

Spell_Resistance::Spell_Resistance( const bool resistance,
				    const bool harmless,
				    const bool see_text)
  : resistance_(resistance),
    harmless_(harmless),
    see_text_(see_text)
{
}

std::string Spell_Resistance::print()
{
  std::string result;
  if ( resistance_ )
    result = "Yes";
  else
    result = "No";

  if ( harmless_ )
    {
      if ( see_text_ )
	return ( result += " (harmless, see text)" );
      else
	return ( result += " (harmless)" );
    }
  else
    {
      if ( see_text_ )
	return ( result += " (see text)" );
      else
	return result;
    }
}
