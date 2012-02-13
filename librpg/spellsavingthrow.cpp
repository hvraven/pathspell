#include "spellelements.h"
#include "spelltoken.h"
#include "strmanip.h"
#include <stdexcept>

using namespace RPG::Pathfinder;

Spell_Saving_Throw::Spell_Saving_Throw()
: type_(),
  value_(Nil),
  harmless_(false),
  see_text_(false),
  object_(false)
{
}

Spell_Saving_Throw::Spell_Saving_Throw (const Saving_Throw_Value_Token& value)
: type_(),
  value_(value),
  harmless_(false),
  see_text_(false),
  object_(false)
{
}

Spell_Saving_Throw::Spell_Saving_Throw
    (const Saving_Throw_Value_Token& value, const Saving_Throw_Token& type)
: type_(type),
  value_(value),
  harmless_(false),
  see_text_(false),
  object_(false)
{
}

std::string
Spell_Saving_Throw::print() const
{
  std::string result;
  switch ( value_ )
  {
    case No:
      {
        result = "No";
        break;
      }
    case Nil:
      break;
    case Negates:
      {
        result = print_type()
          + " negates";
        break;
      }
    case Half:
      {
        result = print_type()
          + " halfs";
        break;
      }
    case Partial:
      {
        result = print_type()
          + " partial";
        break;
      }
    case Disbelief:
      {
        result = print_type()
          + " for disbelief";
        break;
      }
  }

  if ( harmless_ or see_text_ or object_ )
  {
    result += " (";
    if ( harmless_ )
      result += "harmless, ";
    if ( object_ )
      result += "object, ";
    if ( see_text_ )
      result += "see text, ";
    result.erase(result.length() - 2, 2);
    result += ")";
  }
  return result;
}

std::string
Spell_Saving_Throw::print_type() const
{
  switch ( type_ )
  {
    case Will:
      return "Will";
    case Fortitude:
      return "Fort";
    case Reflex:
      return "Ref";
    default:
      return "";
  }
}

void
Spell_Saving_Throw::set_type( const std::string& type )
{
  std::string work = to_lower( type );
  if ( work == "will" )
    type_ = Will;
  else
    if (work == "fort")
      type_ = Fortitude;
    else
      if (work == "ref")
        type_ = Reflex;
      else
        throw std::invalid_argument(type + " is not a valid type");
}

void
Spell_Saving_Throw::set_value( const std::string& value )
{
  const std::string work = to_lower( value );
  if ( ( work == "no" ) or ( work == "none" ) )
    value_ = No;
  else
    if (work == "negates")
      value_ = Negates;
    else
      if ( work == "half")
        value_ = Half;
      else
        if ( work == "partial")
          value_ = Partial;
        else
          if ( work == "disbelief" )
            value_ = Disbelief;
          else
            if ( work == "" )
              value_ = Nil;
            else
              throw std::invalid_argument(value + " is not a valid value");
}
