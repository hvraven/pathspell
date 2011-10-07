#include "strmanip.h"

#include <cctype>

std::string to_lower( const std::string& input )
{
  std::string work;
  for ( std::string::const_iterator it = input.begin() ;
	it != input.end() ; it++ )
    work.push_back( tolower(*it) );
  return work;
}

void str_lower( std::string& input )
{
  for ( std::string::iterator it = input.begin() ;
	it != input.end() ; it++)
    *it = ( tolower(*it) );
}

std::string to_upper( const std::string& input )
{
  std::string work;
  for ( std::string::const_iterator it = input.begin() ;
	it != input.end() ; it++ )
    work.push_back( toupper(*it) );
  return work;
}

void str_upper( std::string& input )
{
  for ( std::string::iterator it = input.begin() ;
	it != input.end() ; it++)
    *it = ( toupper(*it) );
}
