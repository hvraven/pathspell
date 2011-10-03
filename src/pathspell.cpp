#include "xml.h"
#include "gtkwindow.h"

#include <gtkmm/main.h>

int main( int argc, char* argv[] )
{
  Gtk::Main kit(argc, argv);

  Spells spells( "./spells.xml" );

  Gtk_Window window( spells.get_spell_list() );
  Gtk::Main::run(window);

  return 0;
}
