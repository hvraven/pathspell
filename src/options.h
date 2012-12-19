#ifndef SPELLS_OPTIONS_H
#define SPELLS_OPTIONS_H

#include "filter.h"

enum class output_type : int
{
  full,
  list
};

struct options
{
  options();

  filter filter;
  output_type output_type;
  bool exact_match;

  void parse_args(int argc, char** argv);
};

extern options options;

#endif /* SPELLS_OPTIONS_H */
