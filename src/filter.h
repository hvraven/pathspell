#ifndef SPELLS_FILTER_H
#define SPELLS_FILTER_H

#include <iterator>
#include <map>
#include <memory>
#include <regex>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "output.h"
#include "spells.h"
#include "util.h"

class filter_rule
{
public:
  virtual bool operator()(const spell_type& s) = 0;
};

class regex_filter : public filter_rule
{
public:
  template <class U, class V>
  regex_filter(U&& attr, V&& rgx)
      : attribute(std::forward<U>(attr)),
        match(std::forward<V>(rgx), std::regex_constants::icase) {}

  bool operator()(const spell_type& s) override
    { return regex_search(s.find(attribute)->second, match); }

  const std::string attribute;
  const std::regex match;
};

class name_filter : public filter_rule
{
public:
  template <typename... Args>
  name_filter(Args&&... args) : names{std::forward<Args>(args)...} {}
  bool operator()(const spell_type& s) override
    { return (names.find(to_lower(s.find("name")->second)) != end(names)); }

private:
  std::set<std::string> names;
};

class filter
{
public:
  filter() = default;
  filter(std::string&& expr) : rules() { parse_filter(move(expr)); }

  bool match(const spell_type& value) const;

  template <typename Fun>
  void for_matching(const class spells& cont, const Fun&& fun) const;
  void print_matching(const class spells& cont) const
    { for_matching(cont, print_spell); }

  void parse_filter(std::string&& expr);
  template <typename T, typename... Args>
  void add_filter(Args&&... args)
    { rules.emplace_back(std::unique_ptr<filter_rule>
                         {new T{std::forward<Args>(args)...}}); }

  std::vector<std::unique_ptr<filter_rule>> rules;
};

class filter_iterator
  : public std::iterator<std::forward_iterator_tag, spell_type>
{
public:
  filter_iterator()
    : spells_current{}, spells_last{}, filter{}, end{true} {}
  filter_iterator(const spells::iterator& first,
                  const spells::iterator& last,
                  const class filter& f);

  filter_iterator& operator++()
    { find_next_match(); return *this; }
  filter_iterator  operator++(int)
    { auto tmp = *this; find_next_match(); return tmp; }
  bool operator==(const filter_iterator& it2)
    { return ((end && it2.end) || spells_current == it2.spells_current); }
  bool operator!=(const filter_iterator& it2)
    { return ! (*this == it2); }
  reference operator*()
    { return *spells_current; }

private:
  spells::iterator spells_current;
  const spells::iterator spells_last;
  const class filter& filter;
  bool end;

  void find_next_match();
};

template <typename Fun>
void
filter::for_matching(const class spells& cont, const Fun&& fun) const
{
  for (auto e : cont)
    if (match(e))
      fun(e);
}

#endif /* SPELLS_FILTER_H */
