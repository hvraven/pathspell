#include "gtkwindow.h"
#include "spell.h"
#include "storage.h"
#include "xmlspell.h"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gtkmm/main.h>

#include <fstream>
#include <string>
#include <vector>

using namespace RPG;
using namespace RPG::Pathfinder;

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
  std::vector<std::string> path_list;
#ifdef HAVE_CONFIG_H
  path_list.push_back("/usr/share/" PACKAGE "/");
  path_list.push_back("/usr/share/" PACKAGE "-" PACKAGE_VERSION "/");
#endif /* HAVE_CONFIG_H */
  path_list.push_back("./");
  path_list.push_back("../");

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

  RPG::Pathfinder::Xml_Spell_Access spell_access(spell_list_path);
  RPG::Spell_Storage spell_list;
  for (auto e : spell_access)
    spell_list.insert(make_pair(e.get_identifier(), e));
  Gtk_Window window(spell_list);

  Gtk::Main::run(window);

  return 0;
}
