#include "spells.h"

#include "csv.h"
#include "util.h"

#include <functional>
#include <regex>
using namespace std;
using namespace std::placeholders;

void
spells::load_spells(const std::string& file)
{
  clear();
  CSV::indexed_stream input{file, '\t'};
  while (input)
    emplace_back(input.read_line());
}

spells::iterator
spells::find(const std::string& name)
{
  const regex rgx{name, regex_constants::icase};
  return find_if(begin(), end(),
                 [&](const spell_type& s)
                   { return regex_match(s.find("name")->second, rgx); });
}

spells::const_iterator
spells::find(const std::string& name) const
{
  const regex rgx{name, regex_constants::icase};
  return find_if(begin(), end(),
                 [&](const spell_type& s)
                   { return regex_match(s.find("name")->second, rgx); });
}
