#ifndef LIBRPG_PATHFINDER_SPELL_H
#define LIBRPG_PATHFINDER_SPELL_H

#include "element.h"
#include "spellelements.h"
#include <string>

namespace RPG
{
  namespace Pathfinder
  {

    class Spell : public RPG::Element
    {
    public:
      Spell();
      virtual ~Spell();

      virtual const Identifier& get_identifier() const { return name_; }

      void set_name(const std::string& name) { name_ = name; }
      void set_school(const Spell_School& school) { school_ = school; }
      void set_levels(const Spell_Level& level) { level_ = level; }
      void add_level(const std::string& level, const int value)
        { level_.add_level(level, value); }
      void set_casting_time(const Spell_Casting_Time& casting_time)
        { casting_time_ = casting_time; }
      void set_components(const Spell_Components& components)
        { components_ = components; }
      void set_component_verbal(const bool value)
        { components_.set_verbal(value); }
      void set_component_somatic(const bool value)
        { components_.set_somatic(value); }
      void set_component_material(const bool value,
                                  const std::string& description)
        { components_.set_material(value, description); }
      void set_component_focus(const bool value,
                               const std::string& description)
        { components_.set_focus(value, description); }
      void set_component_divine_focus(const bool value)
        { components_.set_divine_focus(value); }
      void set_range(const Spell_Range& range) { range_ = range; }
      void set_duration(const Spell_Duration& duration)
        { duration_ = duration; }
      void set_saving_throw(const Spell_Saving_Throw& saving_throw)
        { saving_throw_ = saving_throw; }
      void set_spell_resistance(const Spell_Spell_Resistance& spell_resistance)
        { spell_resistance_ = spell_resistance; }
      void set_description(const std::string& description)
        { description_ = description; }

      const std::string& get_name() const { return name_; }
      const Spell_School& get_school() const { return school_; }
      const Spell_Level& get_level() const { return level_; }
      const Spell_Casting_Time& get_casting_time() const
        { return casting_time_; }
      const Spell_Components& get_components() const { return components_; }
      const Spell_Range& get_range() const { return range_; }
      const Spell_Duration& get_duration() const { return duration_; }
      const Spell_Saving_Throw& get_saving_throw() const
        { return saving_throw_; }
      const Spell_Spell_Resistance& get_spell_resistance() const
        { return spell_resistance_; }
      const std::string& get_description() const { return description_; }


    private:
      std::string name_;
      Spell_School school_;
      Spell_Level level_;
      Spell_Casting_Time casting_time_;
      Spell_Components components_;
      Spell_Range range_;
      Spell_Duration duration_;
      Spell_Saving_Throw saving_throw_;
      Spell_Spell_Resistance spell_resistance_;
      std::string description_;
    };

  } /* namespace Pathfinder */
} /* namespace RPG */

#endif /* LIBRPG_PATHFINDER_SPELL_H */
