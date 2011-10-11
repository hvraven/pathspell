#ifndef PATHSPELL_XML_H
#define PATHSPELL_XML_H

#define TIXML_USE_STL

#include <tinyxml.h>
#include <string>
#include <map>
#include <vector>

#include "token.h"
#include "spell.h"

struct Spell_Tag
{
  TiXmlElement* pxml;
  Spell* pspell;
  bool cache_valid;

  Spell_Tag()
    : pxml(0), pspell(0), cache_valid(false) {};
  virtual ~Spell_Tag() {};
};

typedef std::map < std::string, Spell_Tag > spell_map;

class Spell_List
{
public:
  Spell_List();
  Spell_List( TiXmlDocument& );
  virtual ~Spell_List();

  TiXmlElement* find_spell( const std::string& );
  void fill_list ( TiXmlDocument& );
  std::vector < std::string > get_spell_list();
  Spell& get_spell( const std::string& );

private:
  spell_map spell_list_;

  void read_spell_( Spell_Tag* );
  void read_spell_( const std::string& );

  void add_elements_( Spell*, TiXmlElement const * const};
};

class Spells
{
public:
  Spells(const char*);
  virtual ~Spells();

  Spell get_spell( const std::string& );
  std::vector < std::string > get_spell_list()
    { return spells_.get_spell_list(); };

private:
  TiXmlDocument doc_;
  Spell_List spells_;

  void add_element_ ( TiXmlElement const * const, Spell& );

  void add_name_( TiXmlElement const * const, Spell& );

  School get_spell_school_( TiXmlElement* );
  Level get_spell_level_( TiXmlElement* );
  Spell_Base_Element get_spell_casting_time_( TiXmlElement* pspell)
    { return get_spell_spell_element_( pspell, "casting_time" ); };
  Components get_spell_components_( TiXmlElement* );
  Spell_Base_Element get_spell_range_( TiXmlElement* pspell)
    { return get_spell_spell_element_( pspell, "range" ); };
  Spell_Base_Element get_spell_duration_( TiXmlElement* pspell )
    { return get_spell_spell_element_( pspell, "duration" ); };
  Saving_Throw get_spell_saving_throw_( TiXmlElement* );
  Spell_Resistance get_spell_spell_resistance_( TiXmlElement* );
  std::string get_spell_description_( TiXmlElement* );
  std::string get_spell_link_( TiXmlElement* );
  Spell_Base_Element get_spell_spell_element_( TiXmlElement*, const std::string&);
  bool check_spell_target_( TiXmlElement* );
  Target* get_spell_target_( TiXmlElement* );
};

#endif // PATHSPELL_XML_H
