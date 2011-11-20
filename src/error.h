#ifndef PATHSPELL_ERROR_H
#define PATHSPELL_ERROR_H

#include <exception>

#include "token.h"

struct File_Load_Error : public std::exception
{
  File_Load_Error() {};
};

struct Invalid_Argument : public std::exception
{
  Invalid_Argument() {};
};

struct Invalid_Attribute : public std::exception
{
  Invalid_Attribute() {};
};

struct Invalid_Pointer : public std::exception
{
  Invalid_Pointer() {};
};

struct Missing_Element : public std::exception
{
  Spell_Element_Token element;

  Missing_Element ( Spell_Element_Token eelement)
    : element(eelement) {};
};

struct Unclear_Arguments : public std::exception
{
  Unclear_Arguments() {};
};

#endif // PATHSPELL_ERROR_H
