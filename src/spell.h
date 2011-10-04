#ifndef PATHSPELL_SPELL_H
#define PATHSPELL_SPELL_H

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

  std::string print();
  std::string print_school() { return school_; };
  std::string print_subschools();
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

struct Spell
{
  std::string name;
  School school;
  //Level level;
  //Casting_Time casting_time;
  //Component component;
  //Range range;
  //Duration duration;
  //Saving_Throw saving_throw;
  //Spell_Resistance spell_resistance;
  std::string description;
  std::string link;
};

#endif // PATHSPELL_SPELL_H
