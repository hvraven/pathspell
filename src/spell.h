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

class Components
{
public:
  Components( const bool = false, const bool = false, const bool = false,
	      const bool = false, const bool = false);
  Components( const bool, const bool, const bool, const bool, const bool,
	      const std::string&, const std::string& = "" );
  virtual ~Components() {};

  void set_verbal( const bool value ) { verbal_ = value; };
  void set_somatic( const bool value ) { somatic_ = value; };
  void set_material( const bool value ) { material_ = value; };
  void set_material( const bool value, const std::string& description )
    { material_ = value; material_description_ = description; };
  void set_focus( const bool value ) { focus_ = value; };
  void set_focus( const bool value, const std::string& description )
    { focus_ = value; focus_description_ = description; };
  void set_divine_focus( const bool value ) { divine_focus_ = value; };

  bool get_verbal() { return verbal_; };
  bool get_somatic() { return somatic_; };
  bool get_material() { return material_; };
  std::string& get_material_description() { return material_description_; };
  bool get_focus() { return focus_; };
  std::string& get_focus_description() { return focus_description_; };
  bool get_divine_focus() { return divine_focus_; };

  std::string print( const bool with_description = true );

private:
  bool verbal_;
  bool somatic_;
  bool material_;
  bool focus_;
  bool divine_focus_;
  std::string material_description_;
  std::string focus_description_;
};

enum Saving_Throw_Token
  {
    WILL,
    FORT,
    REF
  };

enum Saving_Throw_Value_Token
  {
    HALF,
    NEGATES,
    NO
  };

class Saving_Throw
{
public:
  Saving_Throw();
  Saving_Throw( const Saving_Throw_Value_Token& );
  Saving_Throw( const Saving_Throw_Value_Token&,
		const Saving_Throw_Token& );
  virtual ~Saving_Throw() {};

  std::string print();
  std::string print_type();

  Saving_Throw_Token& get_type() { return type_; };
  Saving_Throw_Value_Token& get_value() { return value_; };
  bool get_harmless() { return harmless_; };
  bool get_see_text() { return see_text_; };

  void set_type( const Saving_Throw_Token& type ) { type_ = type; };
  void set_value( const Saving_Throw_Value_Token& value ) { value_ = value; };
  void set_harmless( const bool harmless ) { harmless_ = harmless; };
  void set_see_text( const bool see_text ) { see_text_ = see_text; };

private:
  Saving_Throw_Token type_;
  Saving_Throw_Value_Token value_;
  bool harmless_;
  bool see_text_;
};

class Spell_Resistance
{
public:
  Spell_Resistance( const bool = false, const bool = false,
		    const bool = false );
  virtual ~Spell_Resistance() {};

  std::string print();

  bool get_spell_resistance() { return resistance_; };
  bool get_harmless() { return harmless_; };
  bool get_see_text() { return see_text_; };

  void set_resistance( const bool resistance )
    { resistance_ = resistance; };
  void set_harmless( const bool harmless )
    { harmless_ = harmless; };
  void set_see_text( const bool see_text )
    { see_text_ = see_text; };

private:
  bool resistance_;
  bool harmless_;
  bool see_text_;
};

class Spell_Element
{
public:
  Spell_Element();
  Spell_Element( const std::string& );
  Spell_Element( const std::string&, const int );
  virtual ~Spell_Element() {};

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
  Components components;
  Spell_Element range;
  Spell_Element duration;
  Saving_Throw saving_throw;
  Spell_Resistance spell_resistance;
  std::string description;
  std::string link;
};

#endif // PATHSPELL_SPELL_H
