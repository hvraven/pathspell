#include "util.h"

#include <algorithm>
#include <cctype>

using namespace std;

string
to_lower(string s)
{
  transform(begin(s), end(s), begin(s), (int(*)(int))tolower);
  return s;
}
