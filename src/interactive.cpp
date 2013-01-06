#include "interactive.h"
#include "filter.h"
#include "output.h"
#include "util.h"

#include <algorithm>
#include <cctype>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
using namespace std::placeholders;

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

interactive_mode::interactive_mode()
    : character{"unknown"},
      spells{}
{
  spells.load_spells("./spell_full.tsv");
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
    print_spell(*it);
  else
    print("Spell \"", input, "\" not found.\n");
}

void
interactive_mode::list_spells(string&& input)
{
  filter f{};

  const regex known_rgx{"known", regex_constants::icase};
  if (regex_search(input, known_rgx))
    {
      input = regex_replace(input, known_rgx, "");
      name_filter filter{character.get_known_spells()};
      f.add_filter(move(filter));
    }

  f.parse_filter(move(input));
  copy(filter_iterator{begin(spells), end(spells), f},
       filter_iterator{}, ostream_iterator<string>(cout, "\n"));
}

void
print_help(string&&)
{
  print(" !/exact  <name>      print spell matching name\n"
        " ?/search <filter>    print spell containing given name\n"
        " c/character          save/load character\n"
        " h/help               print this message\n"
        "   learn  <name>      add spell to list of known spells\n"
        " l/list   <filter>    list spells matching given filter rule\n"
        "\n"
        " Filter rules:\n"
        "   Pairs of attribute=value. If just a value is specified it is assumed\n"
        "   to be a name filter. Values can be any valid regular expression.\n"
        );
}

void
interactive_mode::learn_spell(string&& input)
{
  auto it = spells.find(input);
  if (it != end(spells))
    character.learn_spell(to_lower(move(input)));
  else
    print("Refused to learn unknown spell \"", input, "\"\n");
}

void
interactive_mode::set_character(string&& input)
{
  const map<string, function<void(interactive_mode&)>> functions = {
      { "load",          {&interactive_mode::load_known_spells}      },
      { "save",          {&interactive_mode::save_known_spells}      },
   };

  auto space = find_if(begin(input), end(input), (int(*)(int))isspace);
  auto it = functions.find(string(begin(input), space));
  if (it != end(functions))
    it->second(*this);
  else
    print("Unknown option ", string{begin(input), space},
          " to subcommand character.\n");
}

void
interactive_mode::save_known_spells()
{
  character.save();
  print("Character saved.\n");
}

void
interactive_mode::load_known_spells()
{
  character.load();
  print("Character loaded.\n");
}

void
interactive_mode::parse_commands(string&& input)
{
  // do nothing on empty input
  if (input == string())
    return;

  const map<string, function<void(string&&)>> functions = {
      { "?",         bind(&interactive_mode::search_spell,   *this, _1)},
      { "!",         bind(&interactive_mode::exact_spell,    *this, _1)},
      { "c",         bind(&interactive_mode::set_character,  *this, _1)},
      { "h",         {&print_help}                                     },
      { "l",         bind(&interactive_mode::list_spells,    *this, _1)},
      { "char",      bind(&interactive_mode::set_character,  *this, _1)},
      { "character", bind(&interactive_mode::set_character,  *this, _1)},
      { "exact",     bind(&interactive_mode::exact_spell,    *this, _1)},
      { "help",      {&print_help}                                     },
      { "learn",     bind(&interactive_mode::learn_spell,    *this, _1)},
      { "list",      bind(&interactive_mode::list_spells,    *this, _1)},
      { "search",    bind(&interactive_mode::search_spell,   *this, _1)},
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
