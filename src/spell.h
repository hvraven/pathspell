#ifndef PATHSPELL_SPELL_H
#define PATHSPELL_SPELL_H

#include <vector>
#include <string>
#include <map>

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

  void set_school(const std::string school)
    { school_ = school; };
  void add_subschool(const std::string subschool)
    { subschools_.push_back( subschool ); };
  void remove_subschool(const std::string);
  void reset_subschools();

private:
  std::string school_;
  std::vector < std::string > subschools_;
};

typedef std::map < std::string, int > levelmap;

class Level
{
public:
  Level();
  Level( const levelmap& );
  virtual ~Level();

  std::string print();
  std::string print( const std::string& );

  int get_level( const std::string& level )
    { return levels_[level]; };

  void add_level( const levelmap& levels )
    { levels_ = levels; };
  void add_level( const std::string& level, const int value )
    { levels_[level] = value; };
  void remove_level( const std::string& );

private:
  levelmap levels_;
};

class Spell_Element
{
public:
  Spell_Element();
  Spell_Element( const std::string& );
  Spell_Element( const std::string&, const int );
  virtual ~Casting_Time() {};

  virtual std::string print();

  void set( const std::string& type )
    { type_ = type; };
  void set( const int value )
    { value_ = value; };
  void set( const std::string& type, const int value )
    { type_ = type; value_ = value; };

protected:
  std::string type_;
  int value_;
};

struct Spell
{
  std::string name;
  School school;
  Level level;
  Spell_Element casting_time;
  //Component component;
  Spell_Element range;
  Spell_Element duration;
  //Saving_Throw saving_throw;
  //Spell_Resistance spell_resistance;
  std::string description;
  std::string link;
};

#endif // PATHSPELL_SPELL_H
