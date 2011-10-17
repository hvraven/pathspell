#ifndef PATHSPELL_TOKEN_H
#define PATHSPELL_TOKEN_H

// seems to be a default preprocessor variable
#undef DOMAIN

enum Spell_Element_Token
  {
    NAME,
    NAME_LANGUAGE,
    SCHOOL,
    LEVEL,
    LEVEL_TYPE,
    LEVEL_VALUE,
    CASTING_TIME,
    CASTING_TIME_TYPE,
    COMPONENTS,
    RANGE,
    DURATION,
    SAVING_THROW,
    SPELL_RESISTANCE,
    DESCRIPTION,
    LINK,
    TARGET,
    ANNOTATION,
    NOTE,
    AREA,
    SHORT_DESCRIPTION,
    DOMAIN
  };

enum Target_Type_Token
  {
    CREATURE,
    LIVING_CREATURE,
    YOU,
    OBJECT,
    SPECIAL
  };

enum Saving_Throw_Token
  {
    WILL,
    FORT,
    REF
  };

enum Saving_Throw_Value_Token
  {
    NIL,
    HALF,
    NEGATES,
    NO,
    PARTIAL,
    DISBELIEF
  };

#endif // PATHSPELL_TOKEN_H
