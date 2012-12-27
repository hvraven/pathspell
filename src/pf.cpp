#include "interactive.h"
#include "options.h"
#include "output.h"

int main(int argc, char** argv)
{
  options.parse_args(argc, argv);

  if (options.interactive)
    {
      interactive_mode mode;
      mode.run();
    }
  else
    {
      class spells spells;
      spells.load_spells("./spell_full.tsv");
      for (auto spell : spells)
        if (options.filter.match(spell))
          print_spell(spell);
    }
}
