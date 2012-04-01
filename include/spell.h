#ifndef LIBRPG_PATHFINDER_SPELL_H
#define LIBRPG_PATHFINDER_SPELL_H

#include "element.h"
#include "spellelements.h"
#include <string>

namespace RPG
{
  namespace Pathfinder
  {

    struct Spell : public RPG::Element
    {
      const Identifier& get_identifier() const
        { return name; }

      std::string name;
      Spell_School school;
      Spell_Levels levels;
      Spell_Casting_Time casting_time;
      Spell_Components components;
      Spell_Range range;
      Spell_Duration duration;
      Spell_Saving_Throw saving_throw;
      Spell_Spell_Resistance spell_resistance;
      std::string description;
    };

  } /* namespace Pathfinder */
} /* namespace RPG */

#endif /* LIBRPG_PATHFINDER_SPELL_H */
