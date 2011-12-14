#include "spell.h"

#include "error.h"
#include "strmanip.h"

#include <sstream>

Spell_Base_Element::Spell_Base_Element()
  : type_(),
    value_(0)
{
}

Spell_Base_Element::Spell_Base_Element( const std::string& type )
  : type_(type),
    value_(0)
{
}

Spell_Base_Element::Spell_Base_Element( const std::string& type,
                                        const int value )
  : type_(type),
    value_(value)
{
}

std::string Spell_Base_Element::print()
{
  if ( type_ != "" )
    {
      if ( value_ )
	{
	  std::ostringstream sresult;
	  sresult << value_
		  << " "
		  << type_;
	  return sresult.str();
	}
      else
	return type_;
    }
  else
    return "";
}

Spell::Spell()
  : elements_(),
    name_(),
    school_(),
    level_(),
    casting_time_(),
    components_(),
    range_(),
    duration_(),
    saving_throw_(),
    spell_resistance_(),
    description_()
    //    link_()
{
  base_fill_elements_();
}

Spell::~Spell()
{
  std::map<Spell_Element_Token, Spell_Element*>::const_iterator it
    = elements_.begin();
  for ( ; it != elements_.end() ; it++ )
    {
      switch( it->first )
	{
	case NAME:
	case SCHOOL:
	case LEVEL:
	case CASTING_TIME:
	case COMPONENTS:
	case RANGE:
	case DURATION:
	case SAVING_THROW:
	case SPELL_RESISTANCE:
	case DESCRIPTION:
	  break;
	default:
	  delete it->second;
	}
    }
}

Spell_Element& Spell::operator[]( const Spell_Element_Token& element )
{
  return *( elements_[ element ]);
}

void Spell::add_element( const Spell_Element_Token& token,
                         const Spell_Element& element )
{
  // get elements working only with pointers
  if ( token == TARGET )
    {
      if ( elements_[ TARGET ] )
        delete elements_[ TARGET ];
      Target* ptarget = new Target( static_cast<const Target&>(element) );
      elements_[ token ] = ptarget;
    }
  else
    {
      if ( token == NAME )
        name_ = Spell_String_Element("ADD_ELEMENT_TESTSTRING");
      else
        *(elements_[ token ]) = element;
    }
}

void Spell::base_fill_elements_()
{
  elements_[NAME] = &name_;
  elements_[SCHOOL] = &school_;
  elements_[LEVEL] = &level_;
  elements_[CASTING_TIME] = &casting_time_;
  elements_[COMPONENTS] = &components_;
  elements_[RANGE] = &range_;
  elements_[DURATION] = &duration_;
  elements_[SAVING_THROW] = &saving_throw_;
  elements_[SPELL_RESISTANCE] = &spell_resistance_;
  elements_[DESCRIPTION] = &description_;
  //elements_[LINK] = &link_;
}

/**** Duration ***************************************************************/
Duration::Duration()
  : Spell_Base_Element(),
    per_level_(0),
    dismissible_(false)
{
}

Duration::Duration( const std::string& type, const int value,
                    const unsigned int per_level, const bool dismissible )
  : Spell_Base_Element( type, value ),
    per_level_(per_level),
    dismissible_( dismissible )
{
}

/**
 * \brief prints the properties of the class
 */
std::string Duration::print()
{
  std::ostringstream output;
  if ( value_ )
    {
      output << value_
             << " "
             << type_;
      if ( per_level_ )
        {
          if ( per_level_ == 1 )
            output << " per level";
          else
            output << " per "
                   << per_level_
                   << " levels";
        }
    }
  else
    output << type_;

  if ( dismissible_ )
    output << " (D)";

  return output.str();
}

/**
 * \brief decodes level information given in one string
 * \param input the input to decode
 *
 * this function reads level from strings as given in the xml and writes
 * the result in the class.
 * The class treats a single number as a level. If a / is found the number
 * after it is treated as the per level argument. If no number is given
 * after the slash a 1 is assumed.
 */
void Duration::read_level( const std::string& input )
{
  size_t pos = input.find('/');

  /// \todo remove that hack
  if ( pos > input.length() )
    pos = 0;

  if ( pos )
    try
      {
        const std::string pre = input.substr(0,pos);
        set_value(to_int(pre));
        if ( input[pos + 1] == '\0' )
          set_per_level(1);
        else
          {
            const std::string post = input.substr(pos+1,input.length() - pos);
            set_per_level(to_uint(post));
          }
      }
    catch ( Invalid_Character e )
      {
        throw Invalid_Element(DURATION_LEVEL);
      }
  else /* pos == npos */
    try
      {
        set_per_level(0);
        set_value(to_int(input));
      }
    catch ( Invalid_Character e )
      {
        throw Invalid_Element(DURATION_LEVEL);
      }
}
