#include "pf.h"
#include "interactive.h"
#include "options.h"
#include "output.h"

class spells spells;

int main(int argc, char** argv)
{
  options.parse_args(argc, argv);

  spells.load_spells("./spell_full.tsv");

  if (options.interactive)
    {
      interactive_mode mode;
      mode.run();
    }
  else
    for (auto spell : spells)
      if (options.filter.match(spell))
        print_spell(spell);
}
