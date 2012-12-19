#include "filter.h"

bool
filter::match(const value_type& value)
{
  for (auto rule : rules)
    if (! std::regex_search(value.find(rule.attribute)->second, rule.match))
      return false;

  return true;
}