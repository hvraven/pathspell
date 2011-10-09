#include "spell.h"
#include "error.h"

#include <sstream>
#include <cctype>

Target::Target( const Target_Type_Token& type)
  : type_(type),
    pdistance_(0),
    pmax_between_(0),
    pspecial_(0),
    pamount_(0)
{
}

Target::~Target()
{
  delete pdistance_;
  delete pmax_between_;
  delete pspecial_;
  delete pamount_;
}

void Target::set_distance ( const std::string& distance )
{
  if ( pdistance_ )
    *pdistance_ = distance;
  else
    pdistance_ = new std::string( distance );
}

void Target::set_max_between ( const int& max_between )
{
  if ( pmax_between_ )
    *pmax_between_ = max_between;
  else
    pmax_between_ = new int( max_between );
}

void Target::set_special ( const std::string& special )
{
  if ( pspecial_ )
    *pspecial_ = special;
  else
    pspecial_ = new std::string(special);
}

void Target::set_amount ( const std::string& input )
{
  if ( pamount_ )
    *pamount_ = read_amount_( input );
  else
    pamount_ = new Amount( read_amount_(input) );
}

void Target::set_amount( const int value, const bool per_level )
{
  if ( pamount_ )
    {
      pamount_->amount = value;
      pamount_->per_level = per_level;
    }
  else
    pamount_ = new Amount( value, per_level );
}

std::string Target::get_distance()
{
  if ( pdistance_ )
    return *pdistance_;
  else
    return "";
}

int Target::get_max_between()
{
  if ( pmax_between_ )
    return *pmax_between_;
  else
    return 0;
}

std::string Target::get_special()
{
  if ( pspecial_ )
    return *pspecial_;
  else
    return "";
}

std::string Target::get_amount()
{
  if ( pamount_ )
    {
      if ( pamount_->per_level )
	{
	  const int amount = pamount_->amount;
	  if ( amount > 0 )
	    {
	      std::ostringstream output;
	      output << amount
		     << " per level";
	      return output.str();
	    }
	  else
	    {
	      std::ostringstream output;
	      output << "1 per "
		     << ( amount * (-1) )
		     << " levels";
	      return output.str();
	    }
	}
      else
	{
	  std::ostringstream output;
	  output << pamount_->amount;
	  return output.str();
	}
    }
  else
    return "";
}

std::string Target::print()
{
  std::ostringstream output;

  switch ( type_ )
    {
    case SPECIAL:
      {
	if ( pspecial_ )
	  output << *pspecial_;
	break;
      }
    case CREATURE:
    case LIVING_CREATURE:
    case OBJECT:
      {
	if ( pamount_ )
	  {
	    if ( pamount_->amount > 0 )
	      output << pamount_->amount << " ";
	    else
	      output << "1 ";

	    if ( type_ == OBJECT )
	      output << "object";
	    else
	      {
		if ( type_ == LIVING_CREATURE )
		  output << "living ";
		output << "creature";
	      }

	    if ( pamount_->per_level )
	      {
		output << " per ";
		if ( pamount_->amount > 0 )
		  output << "level";
		else
		  output << ( pamount_->amount * (-1 ))
			 << " levels";
	      }
	  }
	else
	  {
	    if ( type_ == OBJECT )
	      output << "object";
	    else
	      {
		if ( type_ == LIVING_CREATURE )
		  output << "living ";
		output << "creatures";
	      }
	  }
	break;
      }
    case YOU:
      {
	output << "You";
	break;
      }
    }

  if ( pdistance_ )
    {
      if ( *pdistance_ == "touch" )
	output << " touched";
      else
	output << *pdistance_;
    }

  if ( pmax_between_ )
    if ( *pmax_between_ )
      output << ", no two of which can be more than "
	     << *pmax_between_
	     << " ft. apart.";

  return output.str();
}

Amount Target::read_amount_( const std::string& input )
{
  int first = 0;
  unsigned int length = input.length();
  for ( unsigned int i = 0; i < length; i++ )
    {
      if ( input[i] == '/' )
	{
	  i++;
	  if ( i < length )
	    {
	      int second = 0;
	      for ( ; i < length; i++ )
		{
		  if ( isdigit(input[i]) )
		    {
		      second *= 10;
		      second += input[i] - '0';
		    }
		  else
		    throw Invalid_Argument();
		}
	      if ( first == 1 )
		{
		  Amount temp( second * -1, true );
		  return temp;
		}
	      else
		if ( second == 1 )
		  {
		    Amount temp( first, true );
		    return temp;
		  }
		else
		  throw Invalid_Argument();
	    }
	  else
	    {
	      Amount temp(first, true);
	      return temp;
	    }
	}
      else
	if ( isdigit(input[i]) )
	  {
	    first *= 10;
	    first += input[i] - '0';
	  }
	else
	  throw Invalid_Argument();
	}
      Amount work(first, false);
      return work;
}
