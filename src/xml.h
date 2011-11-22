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
  friend class Spell_RefPtr;

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

  unsigned int find_spell_( const std::string& spell )
    { return spell_name_map_[ spell ]; };

  Spell* get_checked_spell_pointer_( const unsigned int );
  Spell& get_checked_spell_ref_( const unsigned int );

  void check_spell_( spell_list_iterator );

  std::vector < std::string > get_names_( TiXmlElement const * const );

  void decode_elements_( Spell* const, TiXmlElement const * const);
  void decode_name_( Spell* const, TiXmlElement const * const );
  void decode_school_( Spell* const, TiXmlElement const * const );
  void decode_level_( Spell* const, TiXmlElement const * const );
  void decode_casting_time_( Spell *const, TiXmlElement const *const );
  void decode_component_( Spell *const, TiXmlElement const *const );
  void decode_range_( Spell *const, TiXmlElement const *const );
};

class Spell_RefPtr
{
public:
  Spell_RefPtr( Spell_List * const plist, const unsigned int spell );
  Spell_RefPtr( Spell_List * const, const std::string& );
  virtual ~Spell_RefPtr() {};

  Spell& operator*()
    { return plist_->get_checked_spell_ref_( spell_ ); };
  Spell* operator->()
    { return plist_->get_checked_spell_pointer_( spell_ ); };

private:
  Spell_List * const plist_;
  unsigned int spell_;
};

#endif // PATHSPELL_XML_H
