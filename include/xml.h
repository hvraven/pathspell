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

// functions to decode XML element data
inline Name decode_name( const TiXmlElement *const );
void decode_name( Name&, const TiXmlElement *const );
inline School decode_school( const TiXmlElement *const );
void decode_school( School&, const TiXmlElement *const );
inline Level decode_level( const TiXmlElement *const );
void decode_level( Level&, const TiXmlElement *const );
inline Casting_Time decode_casting_time( const TiXmlElement *const );
void decode_casting_time( Casting_Time&, const TiXmlElement *const );
inline Components decode_component( const TiXmlElement *const );
void decode_component( Components&, const TiXmlElement *const );
inline Range decode_range( const TiXmlElement *const );
void decode_range( Range&, const TiXmlElement *const );
inline Duration decode_duration( const TiXmlElement *const );
void decode_duration( Duration&, const TiXmlElement *const );
inline Saving_Throw decode_saving_throw( const TiXmlElement *const );
void decode_saving_throw( Saving_Throw&, const TiXmlElement *const );
inline Spell_Resistance decode_spell_resistance( const TiXmlElement *const );
void decode_spell_resistance( Spell_Resistance&, const TiXmlElement *const );
inline Description decode_description( const TiXmlElement *const );
void decode_description( Description&, const TiXmlElement *const );

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

  void decode_elements_( Spell *const, const TiXmlElement *const );

  std::vector < std::string > get_names_( TiXmlElement const * const );
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
