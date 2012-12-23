#include "spells.h"

#include "csv.h"
#include "util.h"
using namespace std;

void
spells::load_spells(const std::string& file)
{
  clear();
  CSV::indexed_stream input{file, '\t'};
  while (input)
    {
      spell_type temp{input.read_line()};
      emplace(make_pair(to_lower(temp["name"]), temp));
    }
}
