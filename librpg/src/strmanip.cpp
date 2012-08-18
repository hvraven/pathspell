#include "strmanip.h"
#include <cctype>

using namespace RPG;

std::string
RPG::to_lower( const std::string& input )
{
  std::string work;
  for (std::string::const_iterator it = input.begin() ;
       it != input.end() ; it++)
    work.push_back( tolower(*it) );
  return work;
}

void
RPG::str_lower( std::string& input )
{
  for (std::string::iterator it = input.begin() ;
       it != input.end() ; it++)
    *it = ( tolower(*it) );
}

std::string
RPG::to_upper( const std::string& input )
{
  std::string work;
  for (std::string::const_iterator it = input.begin() ;
       it != input.end() ; it++)
    work.push_back( toupper(*it) );
  return work;
}

void
RPG::str_upper( std::string& input )
{
  for (std::string::iterator it = input.begin() ;
       it != input.end() ; it++)
    *it = ( toupper(*it) );
}
