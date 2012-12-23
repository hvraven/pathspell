#include "interactive.h"
#include "output.h"
#include "pf.h"
#include "util.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

inline void
print_prompt()
{
  cout << ">>> ";
}

void
parse_commands(const string& input)
{
  auto it = spells.find(to_lower(input));
  if (it != end(spells))
    print_spell(it->second);
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
  cout << endl;
}
