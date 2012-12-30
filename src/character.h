#ifndef PF_CHARACTER_H
#define PF_CHARACTER_H

#include <set>
#include <string>

class character
{
public:
  character(const std::string& name_)
    : name(name_), known_spells() {}

  template <typename... Args>
  void set_name(Args&&... args) { name = {std::forward<Args>(args)...}; }
  const std::string& get_name() const { return name; }

  void learn_spell (std::string&& name)
    { known_spells.emplace(move(name)); }
  void learn_spell (const std::string& name)
    { known_spells.emplace(name); }
  bool knows_spell(const std::string& name) const
    { return known_spells.find(name) != end(known_spells); }
  const std::set<std::string>& get_known_spells() const
    { return known_spells; }

  void load();
  void save() const;

private:
  std::string name;
  std::set<std::string> known_spells;
};

#endif /* PF_CHARACTER_H */
