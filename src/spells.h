#ifndef PF_SPELLS_H
#define PF_SPELLS_H

#include <map>
#include <string>

typedef std::map<std::string, std::string> spell_type;

class spells : public std::map<std::string, spell_type>
{
public:
  void load_spells(const std::string& file);
};

#endif /* PF_SPELLS_H */
