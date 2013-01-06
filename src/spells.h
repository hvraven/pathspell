#ifndef PF_SPELLS_H
#define PF_SPELLS_H

#include <algorithm>
#include <map>
#include <string>
#include <vector>

#include "util.h"

typedef std::map<std::string, std::string> basic_spell_type;

class spell_type : public basic_spell_type
{
public:
  template <typename... Args>
  constexpr spell_type(Args... args)
    : basic_spell_type(std::forward<Args>(args)...) {}

  operator std::string() const
    { return find("name")->second; }
  bool operator==(std::string&& n) const
    { return to_lower(move(n)) == to_lower(find("name")->second); }
  bool operator==(const std::string& n) const
    { return to_lower(n) == to_lower(find("name")->second); }

  friend std::ostream& operator<<(std::ostream&, const spell_type&);
  friend std::ostream& operator<<(std::ostream&, spell_type&&);
};

inline
std::ostream& operator<<(std::ostream& s, const spell_type& sp)
  { s << sp.find("name")->second; return s; }
inline
std::ostream& operator<<(std::ostream& s, spell_type&& sp)
  { s << sp.find("name")->second; return s; }

class spells : public std::vector<spell_type>
{
public:
  void load_spells(const std::string& file);

  iterator       find(std::string&& name)
    { return std::find(begin(), end(), move(name)); }
  iterator       find(const std::string& name)
    { return std::find(begin(), end(), name); }
  const_iterator find(std::string&& name) const
    { return std::find(begin(), end(), move(name)); }
  const_iterator find(const std::string& name) const
    { return std::find(begin(), end(), name); }
};

#endif /* PF_SPELLS_H */
