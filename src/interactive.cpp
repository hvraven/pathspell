#include "interactive.h"
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
  auto strings{split(input)};
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
