#include "filter.h"

using namespace std;

filter::filter(string&& expr)
  : rules()
{
  parse_filter(move(expr));
}

bool
filter::match(const value_type& value) const
{
  for (auto rule : rules)
    if (! std::regex_search(value.find(rule.attribute)->second, rule.match))
      return false;

  return true;
}

void
filter::parse_filter(string&& expr)
{
  regex rgx{"\\b(.*)=(.*)\\b"};

  for (sregex_iterator it{begin(expr), end(expr), rgx};
       it != sregex_iterator{}; ++it)
    add_filter(string((*it)[1]), string((*it)[2]));
}
