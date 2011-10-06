#include "spell.h"
#include "error.h"

Saving_Throw::Saving_Throw()
  : type_(),
    value_(NIL),
    harmless_(false),
    see_text_(false)
{
}

Saving_Throw::Saving_Throw( const Saving_Throw_Value_Token& value )
  : type_(),
    value_(value),
    harmless_(false),
    see_text_(false)
{
}

Saving_Throw::Saving_Throw( const Saving_Throw_Value_Token& value,
			    const Saving_Throw_Token& type)
  : type_(type),
    value_(value),
    harmless_(false),
    see_text_(false)
{
}

std::string Saving_Throw::print()
{
  if ( value_ == NO )
    if ( see_text_ )
      return "No (see text)";
    else
      return "No";
  else
    if ( value_ == NIL )
      if ( see_text_ )
	return "See Text";
      else
	return "";
    else
      {
	std::string result = print_type();
	result += " ";

	if ( value_ == NEGATES )
	  result += "negates";
	else
	  result += "half";

	if ( harmless_ )
	  {
	    if ( see_text_ )
	      result += " (harmless, see text)";
	    else
	      result += " (harmless)";
	  }
	else
	  if ( see_text_ )
	    result += " (see text)";

	return result;
      }
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
  if ( (type == "will") or (type == "Will") or (type == "WILL") )
    type_ = WILL;
  else
    if ( (type == "fort") or (type == "Fort") or (type == "FORT") )
      type_ = FORT;
    else
      if ( (type == "ref") or (type == "Ref") or (type == "REF") )
	type_ = REF;
      else
	throw Invalid_Argument();
}

void Saving_Throw::set_value( const std::string& value )
{
  if ( (value == "no") or (value == "No") )
    value_ = NO;
  else
    if ( (value == "negates") or (value == "Negates") )
      value_ = NEGATES;
    else
      if ( (value == "half") or (value == "Half") )
	value_ = HALF;
      else
	throw Invalid_Argument();
}
