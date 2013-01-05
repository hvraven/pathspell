#ifndef SPELLS_FILTER_H
#define SPELLS_FILTER_H

#include <iterator>
#include <map>
#include <regex>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "output.h"
#include "spells.h"
#include "util.h"

namespace detail {
  class basic_regex_filter
  {
  protected:
    template <class U, class V>
    constexpr basic_regex_filter(U&& attr, V&& rgx)
        : attribute(std::forward<U>(attr)),
          match(std::forward<V>(rgx), std::regex_constants::icase) {}

    const std::string attribute;
    const std::regex match;
  };
}

class regex_filter : public detail::basic_regex_filter
{
public:
  template <typename... Args>
  regex_filter(Args&&... args)
      : detail::basic_regex_filter{std::forward<Args>(args)...} {}

  bool operator()(const spell_type& s) const
    { return regex_search(s.find(attribute)->second, match); }
};

class exact_regex_filter : public detail::basic_regex_filter
{
public:
  template <typename... Args>
  exact_regex_filter(Args&&... args)
      : detail::basic_regex_filter{std::forward<Args>(args)...} {}

  bool operator()(const spell_type& s) const
    { return regex_match(s.find(attribute)->second, match); }
};

class name_filter
{
public:
  name_filter(const std::set<std::string>& n)
      : names(n) {}

  bool operator()(const spell_type& s) const
    { return (names.find(to_lower(s.find("name")->second)) != end(names)); }

private:
  std::set<std::string> names;
};

class filter
{
public:
  filter() : rules{} {}
  filter(std::string&& expr) : rules{} { parse_filter(move(expr)); }

  bool match(const spell_type& value) const;

  template <typename Fun>
  void for_matching(const class spells& cont, const Fun&& fun) const;
  void print_matching(const class spells& cont) const
    { for_matching(cont, print_spell); }

  void parse_filter(std::string&& expr);
  template <typename T>
  void add_filter(T&& filter)
    { rules.emplace_back(std::forward<T>(filter)); }

private:
  std::vector<std::function<bool(const spell_type&)>> rules;
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
