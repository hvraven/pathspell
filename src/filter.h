#ifndef SPELLS_FILTER_H
#define SPELLS_FILTER_H

#include <map>
#include <regex>
#include <string>
#include <vector>

struct filter_rule
{
  filter_rule(std::string&& attr, std::string&& match);

  std::string attribute;
  std::regex match;
};

class filter
{
public:
  typedef std::map<std::string, std::string> value_type;

  bool match(const value_type& value);

  std::vector<filter_rule> rules;
};

#endif /* SPELLS_FILTER_H */
