#ifndef LIBRPG_PATHFINDER_SPELLELEMENT_H
#define LIBRPG_PATHFINDER_SPELLELEMENT_H

#include "spelltoken.h"
#include <map>
#include <string>
#include <vector>

namespace RPG
{
  namespace Pathfinder
  {

    class Spell_Element
    {
    public:
      Spell_Element() {}
      virtual ~Spell_Element() {}

      virtual std::string print() const = 0;
    };

    /**
     * @brief specialized Spell_Element containing a type and a value
     */
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

    class Spell_School : public Spell_Element
    {
    public:
      Spell_School();
      Spell_School(const std::string&);
      Spell_School(const std::string&, const std::string&);
      Spell_School(const std::string&, const std::string&, const std::string&);
      Spell_School(const std::string&, const std::vector < std::string >);
      virtual ~Spell_School() {}

      virtual std::string print() const;
      const std::string& print_school() const { return school_; }
      std::string print_subschools() const;
      const std::string& print_descriptor() const { return descriptor_; }
      std::vector < std::string > get_subschools() const { return subschools_; }
      const std::string& get_subschool(const int pos = 0) const
        { return subschools_[pos]; }
      int get_number_of_subschools() const { return subschools_.size(); }

      void set_school(const std::string& school)
        { school_ = school; }
      void add_subschool(const std::string& subschool)
        { subschools_.push_back( subschool ); }
      void remove_subschool(const std::string&);
      void reset_subschools();
      void set_descriptor(const std::string& descriptor)
        { descriptor_ = descriptor; }

    private:
      std::string school_;
      std::vector < std::string > subschools_;
      std::string descriptor_;
    };

    typedef std::map < std::string, int > Spell_Level_Map;

    class Spell_Levels : public Spell_Element
    {
    public:
      Spell_Levels();
      Spell_Levels( const Spell_Level_Map& );
      virtual ~Spell_Levels();

      virtual std::string print() const;
      std::string print( const std::string& ) const;

      int get_level( const std::string& level )
        { return levels_[level]; }

      void add_level( const Spell_Level_Map& levels ) { levels_ = levels; }
      void add_level( const std::string& level, const int value )
        { levels_[level] = value; }
      void remove_level( const std::string& );

    private:
      Spell_Level_Map levels_;
    };

    class Spell_Components : public Spell_Element
    {
    public:
      Spell_Components(const bool = false, const bool = false,
                       const bool = false, const bool = false,
                       const bool = false);
      Spell_Components(const bool, const bool, const bool, const bool,
                       const bool, const std::string&,
                       const std::string& = "" );
      virtual ~Spell_Components() {};

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

    /// \todo add support for combined saving throws
    class Spell_Saving_Throw : public Spell_Element
    {
    public:
      Spell_Saving_Throw();
      Spell_Saving_Throw( const Saving_Throw_Value_Token& );
      Spell_Saving_Throw( const Saving_Throw_Value_Token&,
                         const Saving_Throw_Token& );
      virtual ~Spell_Saving_Throw() {};

      virtual std::string print() const;
      std::string print_type() const;

      const Saving_Throw_Token& get_type() const { return type_; };
      const Saving_Throw_Value_Token& get_value() const { return value_; };
      bool get_harmless() const { return harmless_; };
      bool get_see_text() const { return see_text_; };
      bool get_object() const { return object_; };

      void set_type( const Saving_Throw_Token& type ) { type_ = type; };
      void set_type( const std::string& );
      void set_value( const Saving_Throw_Value_Token& value )
        { value_ = value; };
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

    class Spell_Spell_Resistance : public Spell_Element
    {
    public:
      Spell_Spell_Resistance(const bool = false, const bool = false,
                             const bool = false );
      virtual ~Spell_Spell_Resistance() {};

      virtual std::string print() const;

      bool get_spell_resistance() const { return resistance_; };
      bool get_harmless() const { return harmless_; };
      bool get_see_text() const { return see_text_; };

      void set_resistance( const bool resistance )
        { resistance_ = resistance; };
      void set_harmless( const bool harmless ) { harmless_ = harmless; }
      void set_see_text( const bool see_text ) { see_text_ = see_text; }

    private:
      bool resistance_;
      bool harmless_;
      bool see_text_;
    };

    class Spell_Duration : public Spell_Base_Element
    {
    public:
      Spell_Duration();
      Spell_Duration(const std::string&, const int = 0,
                     const unsigned int = 0, const bool = false );
      virtual ~Spell_Duration() {}

      virtual std::string print() const;

      void set_per_level( const unsigned int per_level )
        { per_level_ = per_level; }
      void set_dismissible( const bool dismissible )
        { dismissible_ = dismissible; }

      void read_level( const std::string& );

      unsigned int get_per_level() const { return per_level_; };
      bool get_dismissible() const { return dismissible_; };

    private:
      unsigned int per_level_;
      bool dismissible_;
    };


    // @todo find a solution for those 2
    typedef Spell_Base_Element Spell_Range;
    typedef Spell_Base_Element Spell_Casting_Time;

  } /* namespace Pathfinder */
} /* namespace RPG */

#endif /* LIBRPG_PATHFINDER_SPELLELEMENTS_H  */
