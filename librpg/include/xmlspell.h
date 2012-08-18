#ifndef LIBRPG_PATHFINDER_XMLSPELL_H
#define LIBRPG_PATHFINDER_XMLSPELL_H

#include "spell.h"
#include "xmlaccess.h"

namespace RPG
{

  template <>
  typename Xml_Access<Pathfinder::Spell>::value_type
  Xml_Access<Pathfinder::Spell>::decode(const TiXmlElement *const pxml) const;

  template<>
  Identifier
  Xml_Access<Pathfinder::Spell>::decode_index(const TiXmlElement *const) const;

  template<>
  TiXmlElement
  Xml_Access<Pathfinder::Spell>::encode(const Pathfinder::Spell&) const;

  namespace Pathfinder
  {

    typedef RPG::Xml_Access<RPG::Pathfinder::Spell> Xml_Spell_Access;

  } /* namespace Pathfinder */

} /* namespace RPG */

#endif /* LIBRPG_PATHFINDER_XMLSPELL_H */
