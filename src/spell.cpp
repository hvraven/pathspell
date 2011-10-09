#include "spell.h"

#include <sstream>

Spell_Base_Element::Spell_Base_Element()
  : type_(),
    value_(0)
{
}

Spell_Base_Element::Spell_Base_Element( const std::string& type )
  : type_(type),
    value_(0)
{
}

Spell_Base_Element::Spell_Base_Element( const std::string& type, const int value )
  : type_(type),
    value_(value)
{
}

std::string Spell_Base_Element::print()
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

Spell::Spell()
  : elements_(),
    name_(),
    school_(),
    level_(),
    casting_time_(),
    components_(),
    range_(),
    duration_(),
    saving_throw_(),
    spell_resistance_(),
    description_(),
    link_()
{
  base_fill_elements_();
}

Spell::Spell( const std::string& name, const School& school,
	      const Level& level,
	      const Spell_Base_Element& casting_time, const Components& components,
	      const Spell_Base_Element& range, const Spell_Base_Element& duration,
	      const Saving_Throw& saving_throw,
	      const Spell_Resistance& spell_resistance,
	      const std::string& description, const std::string& link)
  : elements_(),
    name_(name),
    school_(school),
    level_(level),
    casting_time_(casting_time),
    components_(components),
    range_(range),
    duration_(duration),
    saving_throw_(saving_throw),
    spell_resistance_(spell_resistance),
    description_(description),
    link_(link)
{
  base_fill_elements_();
}

Spell::~Spell()
{
  delete elements_[TARGET];
}

Spell_Element& Spell::operator[]( const Spell_Element_Token& element )
{
  return *( elements_[ element ]);
}

void Spell::set_target( Target* const input )
{
  if ( elements_[TARGET] )
    {
      delete elements_[TARGET];
      elements_[ TARGET ] = input;
    }
  else
    elements_[ TARGET ] = input;
}

void Spell::base_fill_elements_()
{
  elements_[NAME] = &name_;
  elements_[SCHOOL] = &school_;
  elements_[LEVEL] = &level_;
  elements_[CASTING_TIME] = &casting_time_;
  elements_[COMPONENTS] = &components_;
  elements_[RANGE] = &range_;
  elements_[DURATION] = &duration_;
  elements_[SAVING_THROW] = &saving_throw_;
  elements_[SPELL_RESISTANCE] = &spell_resistance_;
  elements_[DESCRIPTION] = &description_;
  elements_[LINK] = &link_;
}
