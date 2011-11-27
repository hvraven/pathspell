#include "spell.h"
#include "error.h"
#include "strmanip.h"

Saving_Throw::Saving_Throw()
  : type_(),
    value_(NIL),
    harmless_(false),
    see_text_(false),
    object_(false)
{
}

Saving_Throw::Saving_Throw( const Saving_Throw_Value_Token& value )
  : type_(),
    value_(value),
    harmless_(false),
    see_text_(false),
    object_(false)
{
}

Saving_Throw::Saving_Throw( const Saving_Throw_Value_Token& value,
			    const Saving_Throw_Token& type)
  : type_(type),
    value_(value),
    harmless_(false),
    see_text_(false),
    object_(false)
{
}

std::string Saving_Throw::print()
{
  std::string result;
  switch ( value_ )
    {
    case NO:
      {
	result = "No";
	break;
      }
    case NIL:
      break;
    case NEGATES:
      {
	result = "Negates";
	break;
      }
    case HALF:
      {
	result = "Half";
	break;
      }
    case PARTIAL:
      {
	result = "Partial";
	break;
      }
    case DISBELIEF:
      {
	result = "Disbelief";
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

std::string Saving_Throw::print_type()
{
  switch ( type_ )
    {
    case WILL:
      return "Will";
    case FORT:
      return "Fort";
    case REF:
      return "Ref";
    default:
      return "";
    }
}

void Saving_Throw::set_type( const std::string& type )
{
  std::string work = to_lower( type );
  if ( work == "will" )
    type_ = WILL;
  else
    if (work == "fort")
      type_ = FORT;
    else
      if (work == "ref")
	type_ = REF;
      else
	throw Invalid_Argument();
}

void Saving_Throw::set_value( const std::string& value )
{
  const std::string work = to_lower( value );
  if ( ( work == "no" ) or ( work == "none" ) )
    value_ = NO;
  else
    if (work == "negates")
      value_ = NEGATES;
    else
      if ( work == "half")
	value_ = HALF;
      else
	if ( work == "partial")
	  value_ = PARTIAL;
	else
	  if ( work == "disbelief" )
	    value_ = DISBELIEF;
	  else
	    throw Invalid_Argument();
}
