#ifndef LIBRPG_PATHFINDER_SPELLTOKEN_H
#define LIBRPG_PATHFINDER_SPELLTOKEN_H

namespace RPG
{
  namespace Pathfinder
  {

    enum class Spell_Token
    {
      Name,
      School,
      Level,
      Domain,
      Casting_Time,
      Components,
      Range,
      Duration,
      Saving_Throw,
      Spell_Resistance,
      Short_Description,
      Description,
      Target,
      Annotation,
      Note,
      Area
    };

    enum class Saving_Throw_Token
    {
      Will,
      Fortitude,
      Reflex
    };

    enum class Saving_Throw_Value_Token
    {
      Nil,
      Half,
      Negates,
      No,
      Partial,
      Disbelief
    };

  } /* namespace Pathfinder */
} /* namespace RPG */

#endif /* LIBRPG_PATHFINDER_SPELLTOKEN_H */
