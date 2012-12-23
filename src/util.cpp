#include "util.h"

#include <algorithm>

using namespace std;

string
to_lower(string s)
{
  transform(begin(s), end(s), begin(s), ::tolower);
  return s;
}
