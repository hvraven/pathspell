#include "spell.h"

Saving_Throw::Saving_Throw()
  : type_(),
    value_(),
    harmless_(),
    see_text_()
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
    return "No";
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
