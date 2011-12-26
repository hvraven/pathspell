#include "xml.h"
#include "gtkwindow.h"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gtkmm/main.h>

#include <fstream>
#include <string>
#include <vector>

/**
 * \brief checks if a file exists in filesystem
 * \param filename path to the file to check
 */
bool file_exists(const std::string& filename)
{
  std::ifstream ifile(filename);
  return ifile;
}

/**
 * /param argv ignored
 */
int main( int argc, char* argv[] )
{
  Gtk::Main kit(argc, argv);

  const std::string spell_file_name = "spells.xml";
  std::vector<std::string> path_list = {
#ifdef HAVE_CONFIG_H
    "/usr/share/" PACKAGE "/",
    "/usr/share/" PACKAGE "-" PACKAGE_VERSION "/",
#endif /* HAVE_CONFIG_H */
    "./",
    "../"
  };

  std::string spell_list_path = "";
  for ( std::vector<std::string>::const_iterator it = path_list.begin();
        it != path_list.end(); it++ )
    if ( file_exists( *it + spell_file_name ) )
      {
        spell_list_path = *it + spell_file_name;
        break;
      }

  if ( spell_list_path == "" )
    {
      std::cerr << "No XML file found!" << std::endl
                << std::endl
                << "Searched paths:" << std::endl;
      for (std::vector<std::string>::const_iterator it = path_list.begin();
           it != path_list.end(); it++ )
        std::cerr << *it << spell_file_name << std::endl;
      return 1;
    }

  Spell_List spell_list( spell_list_path );

  Gtk_Window window( &spell_list );
  Gtk::Main::run(window);

  return 0;
}
