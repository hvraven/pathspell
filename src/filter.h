#ifndef SPELLS_FILTER_H
#define SPELLS_FILTER_H

#include <map>
#include <regex>
#include <string>
#include <utility>
#include <vector>

#include "output.h"
#include "spells.h"

struct filter_rule
{
  template <class U, class V>
  filter_rule(U&& attr, V&& rgx)
      : attribute(std::forward<U>(attr)),
        match(std::forward<V>(rgx), std::regex_constants::icase) {}

  const std::string attribute;
  const std::regex match;
};

class filter
{
public:
  filter() = default;
  filter(std::string&& expr) : rules() { parse_filter(move(expr)); }

  typedef std::map<std::string, std::string> value_type;

  bool match(const value_type& value) const;

  template <typename Fun>
  void for_matching(const class spells& cont, const Fun&& fun) const;
  void print_matching(const class spells& cont) const
    { for_matching(cont, print_spell); }

  void parse_filter(std::string&& expr);
  template <typename... Args>
  void add_filter(Args&&... args)
    { rules.emplace_back(std::forward<Args>(args)...); }

  std::vector<filter_rule> rules;
};

template <typename Fun>
void
filter::for_matching(const class spells& cont, const Fun&& fun) const
{
  for (auto e : cont)
    if (match(e.second))
      fun(e.second);
}

#endif /* SPELLS_FILTER_H */
