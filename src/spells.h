#ifndef PF_SPELLS_H
#define PF_SPELLS_H

#include <map>
#include <string>
#include <vector>

typedef std::map<std::string, std::string> spell_type;

class spells : public std::vector<spell_type>
{
public:
  void load_spells(const std::string& file);

  iterator       find(const std::string& name);
  const_iterator find(const std::string& name) const;
};

#endif /* PF_SPELLS_H */
