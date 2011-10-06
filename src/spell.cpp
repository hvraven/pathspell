#include "spell.h"

#include <sstream>

Spell_Element::Spell_Element()
  : type_(),
    value_(0)
{
}

Spell_Element::Spell_Element( const std::string& type )
  : type_(type),
    value_(0)
{
}

Spell_Element::Spell_Element( const std::string& type, const int value )
  : type_(type),
    value_(value)
{
}

std::string Spell_Element::print()
{
  if ( type_ != "" )
    {
      if ( value_ )
	{
	  std::ostringstream sresult;
	  sresult << value_
		  << " "
		  << type_;
	  return sresult.str();
	}
      else
	return type_;
    }
  else
    return "";
}
