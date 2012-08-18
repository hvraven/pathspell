#include "spell.h"
#include "spelltoken.h"
#include "strmanip.h"
#include <stdexcept>

using namespace RPG::Pathfinder;

Spell::Saving_Throw::Saving_Throw()
  : type_(),
    value_(Saving_Throw_Value_Token::Nil),
    harmless_(false),
    see_text_(false),
    object_(false)
{
}

Spell::Saving_Throw::Saving_Throw(const Saving_Throw_Value_Token& value)
  : type_(),
    value_(value),
    harmless_(false),
    see_text_(false),
    object_(false)
{
}

Spell::Saving_Throw::Saving_Throw(const Saving_Throw_Value_Token& value,
                                  const Saving_Throw_Token& type)
  : type_(type),
    value_(value),
    harmless_(false),
    see_text_(false),
    object_(false)
{
}

std::string
Spell::Saving_Throw::print() const
{
  std::string result;
  switch ( value_ )
    {
    case Saving_Throw_Value_Token::No:
      {
        result = "No";
        break;
      }
    case Saving_Throw_Value_Token::Nil:
      break;
    case Saving_Throw_Value_Token::Negates:
      {
        result = print_type()
          + " negates";
        break;
      }
    case Saving_Throw_Value_Token::Half:
      {
        result = print_type()
          + " halfs";
        break;
      }
    case Saving_Throw_Value_Token::Partial:
      {
        result = print_type()
          + " partial";
        break;
      }
    case Saving_Throw_Value_Token::Disbelief:
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
Spell::Saving_Throw::print_type() const
{
  switch ( type_ )
    {
    case Saving_Throw_Token::Will:
      return "Will";
    case Saving_Throw_Token::Fortitude:
      return "Fort";
    case Saving_Throw_Token::Reflex:
      return "Ref";
    default:
      return "";
    }
}

void
Spell::Saving_Throw::set_type(const std::string& type)
{
  std::string work = to_lower( type );
  if ( work == "will" )
    type_ = Saving_Throw_Token::Will;
  else
    if (work == "fort")
      type_ = Saving_Throw_Token::Fortitude;
    else
      if (work == "ref")
        type_ = Saving_Throw_Token::Reflex;
      else
        throw std::invalid_argument(type + " is not a valid type");
}

void
Spell::Saving_Throw::set_value(const std::string& value)
{
  const std::string work = to_lower( value );
  if ( ( work == "no" ) or ( work == "none" ) )
    value_ = Saving_Throw_Value_Token::No;
  else
    if (work == "negates")
      value_ = Saving_Throw_Value_Token::Negates;
    else
      if ( work == "half")
        value_ = Saving_Throw_Value_Token::Half;
      else
        if ( work == "partial")
          value_ = Saving_Throw_Value_Token::Partial;
        else
          if ( work == "disbelief" )
            value_ = Saving_Throw_Value_Token::Disbelief;
          else
            if ( work == "" )
              value_ = Saving_Throw_Value_Token::Nil;
            else
              throw std::invalid_argument(value + " is not a valid value");
}
