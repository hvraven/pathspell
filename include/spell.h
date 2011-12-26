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
  virtual std::string print() const = 0;
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

  virtual std::string print() const;
  const std::string& print_school() const { return school_; };
  std::string print_subschools() const;
  const std::string& print_descriptor() const { return descriptor_; };
  std::vector < std::string > get_subschools() const { return subschools_; };
  const std::string& get_subschool(const int pos = 0) const
    { return subschools_[pos]; };
  int get_number_of_subschools() const { return subschools_.size(); };

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

  virtual std::string print() const;
  std::string print( const std::string& ) const;

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

  bool get_verbal() const { return verbal_; };
  bool get_somatic() const { return somatic_; };
  bool get_material() const { return material_; };
  const std::string & get_material_description() const
    { return material_description_; };
  bool get_focus() const { return focus_; };
  const std::string& get_focus_description() const
    { return focus_description_; };
  bool get_divine_focus() const { return divine_focus_; };

  virtual std::string print() const { return print(true); };
  std::string print( const bool with_description ) const;

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

  virtual std::string print() const;

  void set_type( const Target_Type_Token& type ) { type_ = type; };
  void set_distance ( const std::string& );
  void set_max_between ( const int& );
  void set_special ( const std::string& );
  void set_amount ( const std::string& );
  void set_amount ( const int, const bool );

  const Target_Type_Token& get_type() const { return type_; };
  std::string get_distance() const;
  int get_max_between() const;
  std::string get_special() const;
  std::string get_amount() const;

private:
  Amount read_amount_( const std::string& );

  /// \todo fix that pointer fuck up
  Target_Type_Token type_;
  std::string* pdistance_;
  int* pmax_between_;
  std::string* pspecial_;
  Amount* pamount_;
};

/// \todo add support for combined saving throws
class Saving_Throw : public Spell_Element
{
public:
  Saving_Throw();
  Saving_Throw( const Saving_Throw_Value_Token& );
  Saving_Throw( const Saving_Throw_Value_Token&,
		const Saving_Throw_Token& );
  virtual ~Saving_Throw() {};

  virtual std::string print() const;
  std::string print_type() const;

  const Saving_Throw_Token& get_type() const { return type_; };
  const Saving_Throw_Value_Token& get_value() const { return value_; };
  bool get_harmless() const { return harmless_; };
  bool get_see_text() const { return see_text_; };
  bool get_object() const { return object_; };

  void set_type( const Saving_Throw_Token& type ) { type_ = type; };
  void set_type( const std::string& );
  void set_value( const Saving_Throw_Value_Token& value ) { value_ = value; };
  void set_value( const std::string& );
  void set_harmless( const bool harmless ) { harmless_ = harmless; };
  void set_see_text( const bool see_text ) { see_text_ = see_text; };
  void set_object( const bool object ) { object_ = object; };

private:
  Saving_Throw_Token type_;
  Saving_Throw_Value_Token value_;
  bool harmless_;
  bool see_text_;
  bool object_;
};

class Spell_Resistance : public Spell_Element
{
public:
  Spell_Resistance( const bool = false, const bool = false,
		    const bool = false );
  virtual ~Spell_Resistance() {};

  virtual std::string print() const;

  bool get_spell_resistance() const { return resistance_; };
  bool get_harmless() const { return harmless_; };
  bool get_see_text() const { return see_text_; };

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

  virtual std::string print() const { return str_; };

  void set_text( const std::string& str ) { str_ = str; };

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

  virtual std::string print() const;

  void set_type( const std::string& type )
    { type_ = type; };
  void set_value( const int value )
    { value_ = value; };
  void set( const std::string& type, const int value )
    { type_ = type; value_ = value; };

protected:
  std::string type_;
  int value_;
};

class Duration : public Spell_Base_Element
{
public:
  Duration();
  Duration( const std::string&, const int = 0, const unsigned int = 0,
            const bool = false );
  virtual ~Duration() {};

  virtual std::string print() const;

  void set_per_level( const unsigned int per_level )
    { per_level_ = per_level; };
  void set_dismissible( const bool dismissible )
    { dismissible_ = dismissible; };

  void read_level( const std::string& );

  unsigned int get_per_level() const { return per_level_; };
  bool get_dismissible() const { return dismissible_; };

protected:
  unsigned int per_level_;
  bool dismissible_;
};

typedef Spell_String_Element Name;
typedef Spell_String_Element Description;
typedef Spell_Base_Element Range;
typedef Spell_Base_Element Casting_Time;

class Spell
{
public:
  Spell();
  virtual ~Spell();

  Spell_Element& operator[]( const Spell_Element_Token& );

  void set_name( const Name& name )
    { name_ = name; };
  void set_name( const std::string& name)
    { name_ = Spell_String_Element( name ); };
  void set_school( const School& school )
    { school_ = school; };
  void set_level( const Level& level )
    { level_ = level; };
  void add_level( const std::string& level, const int value )
    { level_.add_level( level, value ); };
  void set_casting_time( const Casting_Time& casting_time )
    { casting_time_ = casting_time; };
  void set_components( const Components& components )
    { components_ = components; };
  void set_component_verbal( const bool value )
    { components_.set_verbal(value); };
  void set_component_somatic( const bool value )
    { components_.set_somatic(value); };
  void set_component_material( const bool value,
                               const std::string& description )
    { components_.set_material(value, description); };
  void set_component_focus( const bool value, const std::string& description )
    { components_.set_focus(value, description); };
  void set_component_divine_focus( const bool value )
    { components_.set_divine_focus(value); };
  void set_range( const Range& range )
    { range_ = range; };
  void set_duration( const Duration& duration )
    { duration_ = duration; };
  void set_saving_throw( const Saving_Throw& saving_throw )
    { saving_throw_ = saving_throw; };
  void set_spell_resistance( const Spell_Resistance& spell_resistance )
    { spell_resistance_ = spell_resistance; };
  void set_description( const Description& description )
    { description_ = description; };

  const Name& get_name() const { return name_; };
  const School& get_school() const { return school_; };
  const Level& get_level() const { return level_; };
  const Casting_Time& get_casting_time() const { return casting_time_; };
  const Components& get_components() const { return components_; };
  const Range& get_range() const { return range_; };
  const Duration& get_duration() const { return duration_; };
  const Saving_Throw& get_saving_throw() const { return saving_throw_; };
  const Spell_Resistance& get_spell_resistance() const
    { return spell_resistance_; };
  const Description& get_description() const { return description_; };

  // doesn't realy work and is not necessary
  void add_element( const Spell_Element_Token&, const Spell_Element&);

  /*bool check_target() { return elements_[TARGET]; };
    void set_target( Target* const );*/

private:
  // TODO: Change to auto_ptr (currently copy does not work)
  std::map< Spell_Element_Token, Spell_Element* > elements_;
  void base_fill_elements_();

  Name name_;
  School school_;
  Level level_;
  Casting_Time casting_time_;
  Components components_;
  Range range_;
  Duration duration_;
  Saving_Throw saving_throw_;
  Spell_Resistance spell_resistance_;
  Description description_;
  //Spell_String_Element link_;
};

#endif // PATHSPELL_SPELL_H
