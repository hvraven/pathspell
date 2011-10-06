#ifndef PATHSPELL_ERROR_H
#define PATHSPELL_ERROR_H

#include <exception>

enum Spell_Element_Token
  {
    NAME,
    SCHOOL,
    LEVEL,
    LEVEL_TYPE,
    LEVEL_VALUE,
    CASTING_TIME,
    COMPONENTS,
    RANGE,
    DURATION,
    SAVING_THROW,
    SPELL_RESISTANCE,
    DESCRIPTION
  };

struct File_Load_Error : public std::exception
{
  File_Load_Error() {};
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
