#ifndef LIBRPG_PATHFINDER_XMLSPELL_H
#define LIBRPG_PATHFINDER_XMLSPELL_H

#include "spell.h"
#include "xmlaccess.h"

namespace RPG
{
  using namespace RPG::Pathfinder;

  // forward declarations for the {de,en}code functions
  std::map<std::string, Spell_Token> generate_elements_map();
  inline std::string decode_name(const TiXmlElement *const);
  void decode_name(std::string&, const TiXmlElement *const);
  inline Spell_School decode_school(const TiXmlElement *const);
  void decode_school(Spell_School&, const TiXmlElement *const);
  inline Spell_Levels decode_level(const TiXmlElement *const);
  void decode_level(Spell_Levels&, const TiXmlElement *const);
  inline Spell_Casting_Time decode_casting_time
  (const TiXmlElement *const);
  void decode_casting_time(Spell_Casting_Time&,
                           const TiXmlElement *const);
  inline Spell_Components decode_component(const TiXmlElement *const);
  void decode_component(Spell_Components&, const TiXmlElement *const);
  inline Spell_Range decode_range(const TiXmlElement *const);
  void decode_range(Spell_Range&, const TiXmlElement *const);
  inline Spell_Duration decode_duration(const TiXmlElement *const);
  void decode_duration(Spell_Duration&, const TiXmlElement *const);
  inline Spell_Saving_Throw decode_saving_throw
  (const TiXmlElement *const);
  void decode_saving_throw(Spell_Saving_Throw&,
                           const TiXmlElement *const);
  inline Spell_Spell_Resistance decode_spell_resistance
  (const TiXmlElement *const);
  void decode_spell_resistance(Spell_Spell_Resistance&,
                               const TiXmlElement *const);
  inline std::string decode_description(const TiXmlElement *const);
  void decode_description(std::string&, const TiXmlElement *const);


  /**
   * @brief reads the elements from the xml and copies them to the Spell
   * @param pxml the element to decode
   * @return new generated spell
   *
   * @todo add a check if all necessary elements have been found
   * @todo add missing components
   * @todo add error handling
   *
   * this function checks element by element what it is and calls the respecting
   * add functions to add them to the given spell.
   */
  template <>
  Xml_Access<Pathfinder::Spell>::value_type
  Xml_Access<Pathfinder::Spell>::decode(const TiXmlElement *const pxml) const
  {
    /* map for easy translation of the names to tokens */
    static std::map < std::string, Spell_Token > elements;
    if (elements.size() == 0)
      elements = generate_elements_map();

    Spell result;

    TiXmlElement const * pelement = pxml->FirstChildElement();
    while (pelement)
      {
        switch(elements[pelement->Value()])
          {
          case Spell_Token::Name:
            decode_name(result.name, pelement);
            break;
          case Spell_Token::School:
            decode_school(result.school, pelement);
            break;
          case Spell_Token::Level:
            decode_level(result.levels, pelement);
            break;
          case Spell_Token::Casting_Time:
            decode_casting_time(result.casting_time, pelement);
            break;
          case Spell_Token::Components:
            decode_component(result.components, pelement);
            break;
          case Spell_Token::Range:
            decode_range(result.range, pelement);
            break;
          case Spell_Token::Duration:
            decode_duration(result.duration, pelement);
            break;
          case Spell_Token::Saving_Throw:
            decode_saving_throw(result.saving_throw, pelement);
            break;
          case Spell_Token::Spell_Resistance:
            decode_spell_resistance(result.spell_resistance, pelement);
            break;
          case Spell_Token::Description:
            decode_description(result.description, pelement);
            break;
          default:
            throw RPG::xml_error("Unknown element " +
                                 pelement->ValueStr() + " found");
          }

        pelement = pelement->NextSiblingElement();
      }

    return result;
  }

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
