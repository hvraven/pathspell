#include "xml.h"
#include "gtkwindow.h"

#include <gtkmm/main.h>

int main( int argc, char* argv[] )
{
  Gtk::Main kit(argc, argv);

  Spell_List spell_list( "/home/hendrik/Code/pathspell/spells.xml" );

  Gtk_Window window( &spell_list );
  Gtk::Main::run(window);

  return 0;
}
