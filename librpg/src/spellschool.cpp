#include "spell.h"
#include <algorithm>

using namespace RPG::Pathfinder;

Spell::School::School()
  : school_(),
    subschools_()
{
}

Spell::School::School(const std::string& school)
  : school_(school),
    subschools_()
{
}

Spell::School::School(const std::string& school,
                      const std::string& subschool)
  : school_(school),
    subschools_(1, subschool)
{
}

Spell::School::School(const std::string& school,
                      const std::string& subschool1,
                      const std::string& subschool2)
  : school_(school),
    subschools_(1, subschool1)
{
  subschools_.push_back(subschool2);
}

Spell::School::School(const std::string& school,
                      const std::vector < std::string > subschools)
  : school_(school),
    subschools_(subschools)
{
}

std::string
Spell::School::print() const
{
  if ( school_ != "" )
    {
      std::string result = school_;
      if ( subschools_.size() )
        {
          result += " ("
            + print_subschools()
            + ")";
        }

      if ( descriptor_ != "" )
        result += " ["
          + print_descriptor()
          + "]";

      return result;
    }
  else
    return "";
}

std::string
Spell::School::print_subschools() const
{
  std::vector <std::string>::const_iterator it = subschools_.begin();
  if ( it != subschools_.end() )
    {
      std::string result = *it++;
      while ( it != subschools_.end() )
        {
          result += ", ";
          result += *it++;
        }
      return result;
    }
  else
    return "";
}

void
Spell::School::remove_subschool(const std::string& subschool)
{
  subschools_.erase( std::find (subschools_.begin(),
                                subschools_.end(), subschool) );
}
