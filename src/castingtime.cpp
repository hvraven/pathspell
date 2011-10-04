#include "spell.h"

#include <sstream>

Casting_Time::Casting_Time()
  : type_(),
    time_(0)
{
}

Casting_Time::Casting_Time( const std::string& type )
  : type_(type),
    time_(0)
{
}

Casting_Time::Casting_Time( const std::string& type, const int time )
  : type_(type),
    time_(time)
{
}

Casting_Time::~Casting_Time()
{
}

std::string Casting_Time::print()
{
  if ( type_ != "" )
    {
      if ( time_ )
	{
	  std::ostringstream sresult;
	  sresult << time_
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
