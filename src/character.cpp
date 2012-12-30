#include "character.h"
#include <pugixml.hpp>
#include <iostream>

using namespace std;
using namespace pugi;

const char* root_node = "character";
const char* spell_known_node = "known_spells";
const char* spell_node = "spell";

void
character::load()
{
  xml_document doc;
  if (! doc.load_file("./save.xml"))
    {
      cerr << "Failed to load character." << endl;
      return;
    }

  auto spells = doc.child(root_node).child(spell_known_node);
  if (! spells)
    {
      cerr << "Didn't find spell known" << endl;
      return;
    }

  known_spells.clear();
  for (auto node : spells.children(spell_node))
    known_spells.emplace(node.child_value());
}

void
character::save() const
{
  xml_document doc;

  auto root = doc.append_child(root_node);

  auto spells = root.append_child(spell_known_node);
  for (const auto& e : known_spells)
    spells.append_child(spell_node).append_child(node_pcdata).set_value(e.c_str());

  doc.save_file("./save.xml");
}
