#ifndef PATHSPELL_XML_H
#define PATHSPELL_XML_H

// activate stl support
#define TIXML_USE_STL

#include <tinyxml.h>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

#include "token.h"
#include "spell.h"

struct Spell_Tag;

typedef std::vector < Spell_Tag > spell_list;
typedef spell_list::iterator spell_list_iterator;
typedef std::map < std::string, unsigned int > spell_name_map;

struct Spell_Tag
{
  TiXmlElement const * pxml;
  Spell* pspell;
  bool cache_valid;

  Spell_Tag()
    : pxml(0), pspell(0), cache_valid(false) {};
  Spell_Tag( TiXmlElement const * n_pxml )
    : pxml(n_pxml), pspell(0), cache_valid(false) {};
  virtual ~Spell_Tag() {};
};

class Spell_List
{
public:
  Spell_List( const std::string& );
  virtual ~Spell_List();

  std::vector < std::string > get_spell_list();
  Spell& get_spell( const std::string& );

private:
  TiXmlDocument doc_;
  spell_list spell_list_;
  spell_name_map spell_name_map_;

  friend void load_spell( Spell_Tag const * const );
  void fill_list_( TiXmlDocument& );
  Spell_Tag* find_spell_( const std::string& );

  void read_spell_( spell_list_iterator );
  void read_spell_( const std::string& );

  void add_elements_( Spell* const, TiXmlElement const * const);
  void add_name_( Spell&, TiXmlElement const * const );
  std::vector < std::string > get_names_( TiXmlElement const * const );
  void add_school_( Spell&, TiXmlElement const * const );
};

/*class Spell_RefPtr
{
  Spell_RefPtr( Spell_List const * const, Spell_Tag const * const );
  Spell_RefPtr( Spell_List const * const, const std::string& );
  virtual ~Spell_RefPtr() {};

  Spell& operator*();
  Spell* operator->();

private:
  spell_map_element const * const pspell_;
  Spell_List const * const plist_;
  Spell_Tag const * const ptag_;

  //friend spell_map_element const * get_spell_element( const std::string& );
  friend void load_spell( Spell_Tag const * const );
  };*/



/*class Spells
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
  };*/

#endif // PATHSPELL_XML_H
