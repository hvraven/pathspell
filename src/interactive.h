#ifndef PF_INTERACTIVE_H
#define PF_INTERACTIVE_H

#include "character.h"
#include "spells.h"
#include <string>

class interactive_mode
{
public:
  interactive_mode();
  void run();

private:
  class character character;
  class spells    spells;

  void search_spell  (std::string&& input);
  void exact_spell   (std::string&& input);
  void list_spells   (std::string&& input);
  void print_help    (std::string&& input);
  void learn_spell   (std::string&& input);
  void set_character (std::string&& input);
  void parse_commands(std::string&& input);

  void load_known_spells();
  void save_known_spells();
};

#endif /* PF_INTERACTIVE_H */
