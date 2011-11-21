#ifndef PATHSPELL_SPELL_H
#define PATHSPELL_SPELL_H

#include "token.h"

#include <vector>
#include <string>
#include <map>

class Spell_Element
{
public:
  Spell_Element() {};
  virtual ~Spell_Element() {};

  // TODO: give string per reference
  virtual std::string print() = 0;
};

class School : public Spell_Element
{
public:
  School();
  School(const std::string&);
  School(const std::string&, const std::string&);
  School(const std::string&, const std::string&, const std::string&);
  School(const std::string&, const std::vector < std::string >);
  virtual ~School() {};

  virtual std::string print();
  std::string& print_school() { return school_; };
  std::string print_subschools();
  std::string& print_descriptor() { return descriptor_; };
  std::vector < std::string > get_subschools() { return subschools_; };
  std::string get_subschool(const int pos = 0) { return subschools_[pos]; };
  int get_number_of_subschools() { return subschools_.size(); };

  void set_school(const std::string& school)
    { school_ = school; };
  void add_subschool(const std::string& subschool)
    { subschools_.push_back( subschool ); };
  void remove_subschool(const std::string&);
  void reset_subschools();
  void set_descriptor(const std::string& descriptor)
    { descriptor_ = descriptor; };

private:
  std::string school_;
  std::vector < std::string > subschools_;
  std::string descriptor_;
};

typedef std::map < std::string, int > levelmap;

class Level : public Spell_Element
{
public:
  Level();
  Level( const levelmap& );
  virtual ~Level();

  virtual std::string print();
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

class Components : public Spell_Element
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

  virtual std::string print() { return print(true); };
  std::string print( const bool with_description );

private:
  bool verbal_;
  bool somatic_;
  bool material_;
  bool focus_;
  bool divine_focus_;
  std::string material_description_;
  std::string focus_description_;
};

struct Amount
{
  Amount( const int value, const bool level )
    : amount(value), per_level(level) {};
  virtual ~Amount() {};

  int amount;
  bool per_level;
};

class Target : public Spell_Element
{
public:
  Target( const Target_Type_Token& = SPECIAL );
  virtual ~Target();

  virtual std::string print();

  void set_type( const Target_Type_Token& type ) { type_ = type; };
  void set_distance ( const std::string& );
  void set_max_between ( const int& );
  void set_special ( const std::string& );
  void set_amount ( const std::string& );
  void set_amount ( const int, const bool );

  Target_Type_Token& get_type() { return type_; };
  std::string get_distance();
  int get_max_between();
  std::string get_special();
  std::string get_amount();

private:
  Amount read_amount_( const std::string& );

  Target_Type_Token type_;
  std::string* pdistance_;
  int* pmax_between_;
  std::string* pspecial_;
  Amount* pamount_;
};

class Saving_Throw : public Spell_Element
{
public:
  Saving_Throw();
  Saving_Throw( const Saving_Throw_Value_Token& );
  Saving_Throw( const Saving_Throw_Value_Token&,
		const Saving_Throw_Token& );
  virtual ~Saving_Throw() {};

  virtual std::string print();
  std::string print_type();

  Saving_Throw_Token& get_type() { return type_; };
  Saving_Throw_Value_Token& get_value() { return value_; };
  bool get_harmless() { return harmless_; };
  bool get_see_text() { return see_text_; };

  void set_type( const Saving_Throw_Token& type ) { type_ = type; };
  void set_type( const std::string& );
  void set_value( const Saving_Throw_Value_Token& value ) { value_ = value; };
  void set_value( const std::string& );
  void set_harmless( const bool harmless ) { harmless_ = harmless; };
  void set_see_text( const bool see_text ) { see_text_ = see_text; };

private:
  Saving_Throw_Token type_;
  Saving_Throw_Value_Token value_;
  bool harmless_;
  bool see_text_;
};

class Spell_Resistance : public Spell_Element
{
public:
  Spell_Resistance( const bool = false, const bool = false,
		    const bool = false );
  virtual ~Spell_Resistance() {};

  virtual std::string print();

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

class Spell_String_Element : public Spell_Element
{
public:
  Spell_String_Element( const std::string& str = "" )
    : str_(str) {};
  virtual ~Spell_String_Element() {};

  virtual std::string print() { return str_; };

private:
  std::string str_;
};

class Spell_Base_Element : public Spell_Element
{
public:
  Spell_Base_Element();
  Spell_Base_Element( const std::string& );
  Spell_Base_Element( const std::string&, const int );
  virtual ~Spell_Base_Element() {};

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

class Spell
{
public:
  Spell();
  /*Spell( const std::string&, const School&, const Level&,
	 const Spell_Base_Element&, const Components&, const Spell_Base_Element&,
	 const Spell_Base_Element&, const Saving_Throw&,
	 const Spell_Resistance&, const std::string&, const std::string&);*/
  virtual ~Spell();

  Spell_Element& operator[]( const Spell_Element_Token& );

  void set_name( const Spell_String_Element& name )
    { name_ = name; };
  void set_name( const std::string& name)
    { name_ = Spell_String_Element( name ); };
  void set_school( const School& school )
    { school_ = school; };
  void set_level( const Level& level )
    { level_ = level; };
  void add_level( const std::string& level, const int value )
    { level_.add_level( level, value ); };
  void set_casting_time( const Spell_Base_Element& casting_time )
    { casting_time_ = casting_time; };

  // doesn't realy work and is not necessary
  void add_element( const Spell_Element_Token&, const Spell_Element&);

  /*bool check_target() { return elements_[TARGET]; };
    void set_target( Target* const );*/

private:
  // TODO: Change to auto_ptr (currently copy does not work)
  std::map< Spell_Element_Token, Spell_Element* > elements_;
  void base_fill_elements_();

  Spell_String_Element name_;
  School school_;
  Level level_;
  Spell_Base_Element casting_time_;
  Components components_;
  Spell_Base_Element range_;
  Spell_Base_Element duration_;
  Saving_Throw saving_throw_;
  Spell_Resistance spell_resistance_;
  Spell_String_Element description_;
  //Spell_String_Element link_;
};

#endif // PATHSPELL_SPELL_H
