#include "csv.h"
#include "options.h"
#include "output.h"

template <typename It, typename T>
It
find_last(It first, It last, const T& value)
{
  for (; first != last; ++first)
    {
      auto next = std::find(first, last, value);
      if (next == last)
        return first;
      first = next;
    }

  return last;
}

int main(int argc, char** argv)
{
  options.parse_args(argc, argv);

  CSV::indexed_stream input("./spell_full.tsv", '\t');

  CSV::indexed_stream::value_type temp;

  std::map<std::string,std::map<std::string, std::string>> spells;

  while(input)
    {
      input >> temp;
      spells[temp["name"]] = temp;
    }

  for (auto spell : spells)
    if (options.filter.match(spell.second))
      print_spell(spell.second);
}
