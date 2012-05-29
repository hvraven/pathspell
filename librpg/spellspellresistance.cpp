#include "spell.h"

using namespace RPG::Pathfinder;

Spell::Resistance::Resistance(const bool resistance, const bool harmless,
                              const bool see_text)
  : resistance_(resistance),
    harmless_(harmless),
    see_text_(see_text)
{
}

std::string
Spell::Resistance::print() const
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
