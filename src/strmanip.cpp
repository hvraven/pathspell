#include "strmanip.h"

#include "error.h"

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

/**
 * \brief converts a string to an int
 * \param input string to convert
 * \todo implement a range check
 * \todo remove .length() from implementation for speed reasons
 */
int to_int( const std::string& input )
{
  switch( input[0] )
    {
    case '+':
      return to_uint(input.substr(1, input.length() - 1));
    case '-':
      return -1 * to_uint(input.substr(1, input.length() - 1));
    default:
      return to_uint( input );
    }
}

/**
 * \brief converts a string to an unsigend int
 * \param input string to convert
 * \todo implement a range check
 *
 * this function tries to convert a string to an unsigned int. If a
 * character inside the text is not a number a Invalid_Character is thrown
 */
unsigned int to_uint( const std::string& input )
{
  unsigned int output = 0;
  for ( std::string::const_iterator it = input.begin() ;
        it != input.end() ; it ++ )
    if ( std::isdigit(*it) )
      output = output * 10 + ( *it - '0' );
    else
      throw Invalid_Character( *it );
  return output;
}
