#include "spell.h"
#include <sstream>

using namespace RPG::Pathfinder;

Spell::Base_Element::Base_Element()
  : type_(),
    value_(0)
{
}

Spell::Base_Element::Base_Element(const std::string& type)
  : type_(type),
    value_(0)
{
}

Spell::Base_Element::Base_Element(const std::string& type,
                                  const int value)
  : type_(type),
    value_(value)
{
}

std::string
Spell::Base_Element::print() const
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
