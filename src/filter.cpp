#include "filter.h"
#include "output.h"
#include "spells.h"

bool
filter::match(const value_type& value) const
{
  for (auto rule : rules)
    if (! std::regex_search(value.find(rule.attribute)->second, rule.match))
      return false;

  return true;
}

void
filter::print_matching(spells& cont) const
{
  for (auto& e : cont)
    if (match(e.second))
      print_spell(e.second);
}
