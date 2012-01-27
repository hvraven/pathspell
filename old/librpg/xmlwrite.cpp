#include "xml.h"

/**
 * \brief adds the given spell to the spell xml
 * \todo add support for multiple languages
 *
 * This function adds a new spell to the xml file. If a spell with the same
 * name is found nothing is added.
 * This function updates the spell_name_map_ of the Spell_List making any
 * iterators from the spell_name_map_ invalid
 */
void Spell_List::add_spell(const Spell& spell)
{
  /* writing data to xml tree */
  TiXmlElement espell("spell");

  TiXmlElement ename("name");
  ename.SetAttribute("language", "en");
  ename.SetValue(spell.get_name().print());
  espell.LinkEndChild(&ename);

  TiXmlElement eschool("school");
  eschool.SetAttribute("type", spell.get_school().print_school());

  /* add xml tree to file */
  TiXmlElement *const proot = doc_.FirstChildElement();
  proot->LinkEndChild(&espell);
  doc_->SaveFile(file_path_);

  /* generating new Spell_Tag and add it to spell_list_ */

  /* update spell_name_map_ */
}
