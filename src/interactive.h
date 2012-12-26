#ifndef PF_INTERACTIVE_H
#define PF_INTERACTIVE_H

#include "character.h"
#include <memory>
#include <string>

class interactive_mode
{
public:
  void run();

private:
  std::unique_ptr<character> ch;

  void search_spell(std::string&& input);
  void exact_spell (std::string&& input);
  void list_spells (std::string&& input);
  void print_help  (std::string&& input);
  void learn_spell (std::string&& input);
  void parse_commands(std::string&& input);
};

#endif /* PF_INTERACTIVE_H */
