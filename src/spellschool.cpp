#include "spellschool.h"

#include <algorithm>

School::School()
  : school_(),
    subschools_()
{
}

School::School(const std::string school)
  : school_(school),
    subschools_()
{
}

School::School(const std::string school, const std::string subschool)
  : school_(school),
    subschools_(1, subschool)
{
}

School::School(const std::string school, const std::string subschool1,
	       const std::string subschool2)
  : school_(school),
    subschools_(1, subschool1)
{
  subschools_.push_back(subschool2);
}

School::School(const std::string school,
	       const std::vector < std::string > subschools)
  : school_(school),
    subschools_(subschools)
{
}

School::~School()
{
}

std::string School::get_subschools_formated()
{
  std::vector <std::string>::const_iterator it = subschools_.begin();
  if ( it != subschools_.end() )
    {
      std::string result = *(it++);
      while ( it != subschools_.end() )
	{
	  result += ", ";
	  result += *it;
	}

      return result;
    }
  else
    return "";
}

void School::remove_subschool(const std::string subschool)
{
  subschools_.erase( std::find ( subschools_.begin(), subschools_.end(), subschool ) );
}
