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

Spell_Base_Element::Spell_Base_Element( const std::string& type,
                                        const int value )
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
    description_()
    //    link_()
{
  base_fill_elements_();
}

Spell::~Spell()
{
  std::map<Spell_Element_Token, Spell_Element*>::const_iterator it
    = elements_.begin();
  for ( ; it != elements_.end() ; it++ )
    {
      switch( it->first )
	{
	case NAME:
	case SCHOOL:
	case LEVEL:
	case CASTING_TIME:
	case COMPONENTS:
	case RANGE:
	case DURATION:
	case SAVING_THROW:
	case SPELL_RESISTANCE:
	case DESCRIPTION:
	  break;
	default:
	  delete it->second;
	}
    }
}

Spell_Element& Spell::operator[]( const Spell_Element_Token& element )
{
  return *( elements_[ element ]);
}

void Spell::add_element( const Spell_Element_Token& token,
                         const Spell_Element& element )
{
  // get elements working only with pointers
  if ( token == TARGET )
    {
      if ( elements_[ TARGET ] )
        delete elements_[ TARGET ];
      Target* ptarget = new Target( static_cast<const Target&>(element) );
      elements_[ token ] = ptarget;
    }
  else
    {
      if ( token == NAME )
        name_ = Spell_String_Element("ADD_ELEMENT_TESTSTRING");
      else
        *(elements_[ token ]) = element;
    }
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
  //elements_[LINK] = &link_;
}
