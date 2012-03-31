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
      void set_casting_time(const Spell_Casting_Time& casting_time)
        { casting_time_ = casting_time; }
      void set_components(const Spell_Components& components)
        { components_ = components; }
      void set_range(const Spell_Range& range) { range_ = range; }
      void set_duration(const Spell_Duration& duration)
        { duration_ = duration; }
      void set_saving_throw(const Spell_Saving_Throw& saving_throw)
        { saving_throw_ = saving_throw; }
      void set_spell_resistance(const Spell_Spell_Resistance& spell_resistance)
        { spell_resistance_ = spell_resistance; }
      void set_description(const std::string& description)
        { description_ = description; }

      std::string& get_name() { return name_; }
      Spell_School& get_school() { return school_; }
      Spell_Level& get_level() { return level_; }
      Spell_Casting_Time& get_casting_time() { return casting_time_; }
      Spell_Components& get_components() { return components_; }
      Spell_Range& get_range() { return range_; }
      Spell_Duration& get_duration() { return duration_; }
      Spell_Saving_Throw& get_saving_throw() { return saving_throw_; }
      Spell_Spell_Resistance& get_spell_resistance()
        { return spell_resistance_; }
      std::string& get_description() { return description_; }

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
