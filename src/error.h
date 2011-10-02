#include <exception>

enum Spell_Element_Token
  {
    NAME
  };

struct Missing_Element : public std::exception
{
  Spell_Element_Token element;

  Missing_Element ( Spell_Element_Token eelement)
    : element(eelement) {};
};

struct File_Not_Found : public std::exception
{
  File_Not_Found() {};
};
