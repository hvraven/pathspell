#ifndef PATHSPELL_SPELLSCHOOL_H
#define PATHSPELL_SPELLSCHOOL_H

#include <vector>
#include <string>

class School
{
public:
  School();
  School(const std::string);
  School(const std::string, const std::string);
  School(const std::string, const std::string, const std::string);
  School(const std::string, const std::vector < std::string >);
  virtual ~School();

  std::string get_school() { return school_; };
  std::string get_subschools_formated();
  std::vector < std::string > get_subschools() { return subschools_; };
  std::string get_subschool(const int pos) { return subschools_[pos]; };
  int get_number_of_subschools() { return subschools_.size(); };

  void set_school(const std::string school) { school_ = school; };
  void add_subschool(const std::string subschool) { subschools_.push_back( subschool ); };
  void remove_subschool(const std::string);
  void reset_subschools();

private:
  std::string school_;
  std::vector < std::string > subschools_;
};

#endif // PATHSPELL_SPELLSCHOOL_H
