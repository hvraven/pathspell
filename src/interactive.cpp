#include "interactive.h"
#include "filter.h"
#include "output.h"
#include "pf.h"
#include "util.h"

#include <algorithm>
#include <cctype>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

inline void
print()
{
}

template <typename T, typename... Args>
inline void
print(T&& first, Args&&... args)
{
  cout << first;
  print(args...);
}

inline void
print_prompt()
{
  print(">>> ");
}

void
interactive_mode::search_spell(string&& input)
{
  filter f{move(input)};
  f.print_matching(spells);
}

void
interactive_mode::exact_spell(string&& input)
{
  auto it = spells.find(to_lower(input));
  if (it != end(spells))
    print_spell(it->second);
  else
    print("Spell \"", input, "\" not found.\n");
}

void
interactive_mode::list_spells(string&& input)
{
  filter f{move(input)};
  f.for_matching(spells, [](spell_type& e){ cout << e["name"] << endl; });
}

void
interactive_mode::print_help(string&&)
{
  print(" !/exact  <name>      print spell matching name\n"
        " ?/search <filter>    print spell containing given name\n"
        " h/help               print this message\n"
        " l/list   <filter>    list spells matching given filter rule\n"
        "\n"
        " Filter rules:\n"
        "   Pairs of attribute=value. If just a value is specified it is assumed\n"
        "   to be a name filter. Values can be any valid regular expression.\n"
        );
}

void
interactive_mode::parse_commands(string&& input)
{
  // do nothing on empty input
  if (input == string())
    return;

  const static map<string, function<void(interactive_mode&, string&&)>> functions = {
      { "?",      {&interactive_mode::search_spell} },
      { "!",      {&interactive_mode::exact_spell}  },
      { "h",      {&interactive_mode::print_help}   },
      { "l",      {&interactive_mode::list_spells}  },
      { "exact",  {&interactive_mode::exact_spell}  },
      { "help",   {&interactive_mode::print_help}   },
      { "list",   {&interactive_mode::list_spells}  },
      { "search", {&interactive_mode::search_spell} },
    };

  auto space = find_if(begin(input), end(input), (int(*)(int))isspace);
  auto it = functions.find(string(begin(input), space));
  if (it != end(functions))
    {
      if (space == end(input))
        it->second(*this, "");
      else
        it->second(*this, string(++space, end(input)));
    }
  else
    search_spell(move(input));
}

void
interactive_mode::run()
{
  string input;
  print_prompt();

  while (getline(cin, input))
    {
      parse_commands(move(input));
      print_prompt();
    }

  // print endline if we leave
  print('\n');
}
