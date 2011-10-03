#ifndef PATHSPELL_SPELL_H
#define PATHSPELL_SPELL_H

#include "spellschool.h"

#include <string>

struct Spell
{
  std::string name;
  School school;
  //Level level;
  //Casting_Time casting_time;
  //Componentes componentes;
  //Range range;
  //Duration duration;
  //Saving_Throw saving_throw;
  //Spell_Resistance spell_resistance;
  std::string description;
  std::string link;
};

#endif // PATHSPELL_SPELL_H
