#include "spell.h"

#include "error.h"
#include "strmanip.h"

#include <sstream>

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
  size_t pos = 0;

  while (input[pos] != '/')
    if (input[pos++] == '\0')
      {
        pos = 0;
        break;
      }

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
