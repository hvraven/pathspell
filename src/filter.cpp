#include "filter.h"

using namespace std;

bool
filter::match(const spell_type& value) const
{
  for (auto& rule : rules)
    if (! (*rule)(value))
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
        add_filter<regex_filter>(remap_it->second, string((*it)[2]));
      else
        add_filter<regex_filter>(string((*it)[1]), string((*it)[2]));
    }
}

filter_iterator::filter_iterator(const spells::iterator& first,
                                 const spells::iterator& last,
                                 const class filter& f)
   : spells_current{first},
     spells_last{last},
     filter{f}
{
  if (! filter.match(*spells_current))
    find_next_match();
}

void
filter_iterator::find_next_match()
{
  for (++spells_current; spells_current != spells_last; ++spells_current)
    if (filter.match(*spells_current))
      return;
}
