#include "spell.h"
#include "error.h"

Components::Components(const bool verbal, const bool somatic,
		       const bool material, const bool focus,
		       const bool divine_focus)
  : verbal_(verbal),
    somatic_(somatic),
    material_(material),
    focus_(focus),
    divine_focus_(divine_focus)
{
}

Components::Components(const bool verbal, const bool somatic,
		       const bool material, const bool focus,
		       const bool divine_focus,
		       const std::string& first_description,
		       const std::string& second_description )
  : verbal_(verbal),
    somatic_(somatic),
    material_(material),
    focus_(focus),
    divine_focus_(divine_focus)
{
  if ( second_description != "" )
    {
      material_description_ = first_description;
      focus_description_ = second_description;
    }
  else
    {
      if ( material_ == focus_ )
	throw Unclear_Arguments();

      if ( material_ )
	material_description_ = first_description;
      else
	focus_description_ = first_description;
    }
}

std::string Components::print( const bool with_description )
{
  std::string result;
  if ( verbal_ )
    result += "V, ";
  if ( somatic_ )
    result += "S, ";
  if ( material_ )
    {
      if ( with_description )
	{
	  result += "M ("
	    + material_description_
	    + "), ";
	}
      else
	result += "M, ";
    }
  if ( focus_ )
    {
      if ( with_description )
	{
	  result += "F ("
	    + focus_description_
	    + "), ";
	}
      else
	result += "F, ";
    }
  if ( divine_focus_ )
    result += "DF, ";

  // cut ", "
  if ( result != "" )
    result.erase( result.end() - 2, result.end() - 1 );

  return result;
}
