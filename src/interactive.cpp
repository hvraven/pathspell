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

static
void
search_spell(string&& input)
{
  filter f{move(input)};
  f.print_matching(spells);
}

static
void
exact_spell(string&& input)
{
  auto it = spells.find(to_lower(input));
  if (it != end(spells))
    print_spell(it->second);
  else
    print("Spell \"", input, "\" not found.\n");
}

static
void
list_spells(string&& input)
{
  filter f{move(input)};
  f.for_matching(spells, [](spell_type& e){ cout << e["name"] << endl; });
}

static
void
print_help(string&&)
{
  print(" !/exact   <name>     print spell matching name\n"
        " ?/search  <name>     print spell containing given name\n"
        " h/help               print this message\n"
        " l/list <attr=value>  list spells matching given filter rule\n");
}

void
parse_commands(string& input)
{
  // do nothing on empty input
  if (input == string())
    return;

  const static map<string, function<void(string&&)>> functions = {
      { "?",      {&search_spell} },
      { "!",      {&exact_spell}  },
      { "h",      {&print_help}   },
      { "l",      {&list_spells}  },
      { "exact",  {&exact_spell}  },
      { "help",   {&print_help}   },
      { "list",   {&list_spells}  },
      { "search", {&search_spell} },
    };

  auto space = find_if(begin(input), end(input), (int(*)(int))isspace);
  auto it = functions.find(string(begin(input), space));
  if (it != end(functions))
    {
      if (space == end(input))
        it->second("");
      else
        it->second(string(++space, end(input)));
    }
  else
    search_spell(move(input));
}

void
interactive_mode()
{
  string input;
  print_prompt();

  while (getline(cin, input))
    {
      parse_commands(input);
      print_prompt();
    }

  // print endline if we leave
  print('\n');
}
