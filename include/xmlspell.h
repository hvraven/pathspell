#ifndef LIBRPG_PATHFINDER_XMLSPELL_H
#define LIBRPG_PATHFINDER_XMLSPELL_H

#include "spell.h"
#include "xmlaccess.h"

namespace RPG
{

  namespace Pathfinder
  {

    class Xml_Spell_Access
      : public RPG::Xml_Access<RPG::Pathfinder::Spell>
    {
    protected:
      Spell decode(const TiXmlElement *const) const;
      Identifier decode_index(const TiXmlElement *const) const;
      TiXmlElement encode(const Spell&) const;

    private:
      inline std::string decode_name(const TiXmlElement *const) const;
      void decode_name(std::string&, const TiXmlElement *const) const;
      inline Spell_School decode_school(const TiXmlElement *const) const;
      void decode_school(Spell_School&, const TiXmlElement *const) const;
      inline Spell_Level decode_level(const TiXmlElement *const) const;
      void decode_level(Spell_Level&, const TiXmlElement *const) const;
      inline Spell_Casting_Time decode_casting_time
        (const TiXmlElement *const) const;
      void decode_casting_time(Spell_Casting_Time&,
                               const TiXmlElement *const) const;
      inline Spell_Components decode_component(const TiXmlElement *const) const;
      void decode_component(Spell_Components&, const TiXmlElement *const) const;
      inline Spell_Range decode_range(const TiXmlElement *const) const;
      void decode_range(Spell_Range&, const TiXmlElement *const) const;
      inline Spell_Duration decode_duration(const TiXmlElement *const) const;
      void decode_duration(Spell_Duration&, const TiXmlElement *const) const;
      inline Spell_Saving_Throw decode_saving_throw
        (const TiXmlElement *const) const;
      void decode_saving_throw(Spell_Saving_Throw&,
                               const TiXmlElement *const) const;
      inline Spell_Spell_Resistance decode_spell_resistance
        (const TiXmlElement *const) const;
      void decode_spell_resistance(Spell_Spell_Resistance&,
                                   const TiXmlElement *const) const;
      inline std::string decode_description(const TiXmlElement *const) const;
      void decode_description(std::string&, const TiXmlElement *const) const;
    };

  } /* namespace Pathfinder */
} /* namespace RPG */

#endif /* LIBRPG_PATHFINDER_XMLSPELL_H */
