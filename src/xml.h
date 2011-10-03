#ifndef PATHSPELL_XML_H
#define PATHSPELL_XML_H

#ifndef TIXML_USE_STL
  #define TIXML_USE_STL
#endif

#include <tinyxml.h>
#include <string>
#include <map>
#include <vector>

#include "spell.h"

class Spell_List
{
public:
  Spell_List();
  Spell_List( TiXmlDocument& );
  virtual ~Spell_List();

  TiXmlElement* find_spell( const std::string );
  void fill_list ( TiXmlDocument& );

private:
  std::map < std::string, TiXmlElement* > spell_list_;
};

class Spells
{
public:
  Spells(const char*);
  virtual ~Spells();

  Spell get_spell( const std::string );
  std::vector < std::string > get_spell_list();

private:
  TiXmlDocument doc_;
  Spell_List spells_;
};

#endif // PATHSPELL_XML_H
