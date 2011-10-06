#include "spell.h"
#include <sstream>

Level::Level()
  : levels_()
{
}

Level::Level( const levelmap& levels)
  : levels_(levels)
{
}

Level::~Level()
{
}

std::string Level::print()
{
  std::ostringstream temp;
  for (levelmap::const_iterator it = levels_.begin() ;
       it != levels_.end() ; it++ )
    {
      temp << it->first
	     << " "
	     << it->second
	     << "; ";
    }
  std::string result = temp.str();
  if ( result != "" )
    result.erase( result.end() - 2, result.end() -1 );

  return result;
}

std::string Level::print( const std::string& level)
{
  if ( levels_[level] )
    {
      std::ostringstream sresult;
      sresult << level
	      << " "
	      << levels_[level];
      return sresult.str();
    }
  else
    return "";
}
