#include "filter.h"

filter_rule::filter_rule(std::string&& attr, std::string&& rgx)
     : attribute(std::move(attr)),
       match(std::move(rgx), std::regex_constants::icase)
{
}

bool
filter::match(const value_type& value)
{
  for (auto rule : rules)
    if (! std::regex_search(value.find(rule.attribute)->second, rule.match))
      return false;

  return true;
}
