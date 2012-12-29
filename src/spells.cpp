#include "spells.h"

#include "csv.h"

void
spells::load_spells(const std::string& file)
{
  clear();
  CSV::indexed_stream input{file, '\t'};
  while (input)
    emplace_back(input.read_line());
}
