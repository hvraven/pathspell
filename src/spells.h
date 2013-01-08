#ifndef PF_SPELLS_H
#define PF_SPELLS_H

#include <algorithm>
#include <map>
#include <string>
#include <vector>

#include "util.h"

class spell_type
{
public:
  using spell_container = std::map<std::string, std::string>;

  template <typename... Args>
  constexpr spell_type(Args... args)
    : c{std::forward<Args>(args)...} {}

  operator std::string() const
    { return c.find("name")->second; }
  bool operator==(std::string&& n) const
    { return to_lower(move(n)) == to_lower(c.find("name")->second); }
  bool operator==(const std::string& n) const
    { return to_lower(n) == to_lower(c.find("name")->second); }

  // Modifiers
  void clear() { c.clear(); }
  template <class... Args>
  std::pair<spell_container::iterator,bool> emplace(Args&&... args)
    { return c.emplace(std::forward<Args>(args)...); }

  // Lookup
  const std::string& operator[](const std::string& attr) const
    { return c.find(attr)->second; }

  friend std::ostream& operator<<(std::ostream&, const spell_type&);
  friend std::ostream& operator<<(std::ostream&, spell_type&&);

private:
  spell_container c;
};

inline
std::ostream& operator<<(std::ostream& s, const spell_type& sp)
  { s << static_cast<std::string>(sp); return s; }
inline
std::ostream& operator<<(std::ostream& s, spell_type&& sp)
  { s << static_cast<std::string>(sp); return s; }

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
