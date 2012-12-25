#include "filter.h"

using namespace std;

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
  // filter rules without space are assumed to be name filters
  const regex name_filter{"(\\s+|^)([^=^[:space:]]+)(\\s+|$)"};
  expr = regex_replace(expr, name_filter, "name=$2");

  const regex rgx{"\\b(\\S+)=(\\S+)\\b"};
  const map<string, string> remap = {
      { "class",    "spell_level"   },
      { "level",    "spell_level"   },
    };

  for (sregex_iterator it{begin(expr), end(expr), rgx};
       it != sregex_iterator{}; ++it)
    {
      auto remap_it = remap.find((*it)[1]);
      if (remap_it != end(remap))
        add_filter(remap_it->second, string((*it)[2]));
      else
        add_filter(string((*it)[1]), string((*it)[2]));
    }
}
