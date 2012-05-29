#include "spell.h"
#include <sstream>
#include <string>

using namespace RPG::Pathfinder;

Spell::Duration::Duration()
  : Base_Element(),
    per_level_(0),
    dismissible_(false)
{
}

Spell::Duration::Duration(const std::string& type, const int value,
                          const unsigned int per_level,
                          const bool dismissible)
  : Base_Element(type, value),
    per_level_(per_level),
    dismissible_( dismissible )
{
}

/**
 * @brief prints the properties of the class
 */
std::string
Spell::Duration::print() const
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
 * @brief decodes level information given in one string
 * @param input the input to decode
 *
 * this function reads level from strings as given in the xml and writes
 * the result in the class.
 * The class treats a single number as a level. If a / is found the number
 * after it is treated as the per level argument. If no number is given
 * after the slash a 1 is assumed.
 */
void
Spell::Duration::read_level( const std::string& input )
{
  size_t pos = 0;

  while (input[pos] != '/')
    if (input[pos++] == '\0')
      {
        pos = 0;
        break;
      }

  if ( pos )
    {
      const std::string pre = input.substr(0,pos);
      set_value(stoi(pre));
      if ( input[pos + 1] == '\0' )
        set_per_level(1);
      else
        {
          const std::string post = input.substr(pos+1,input.length() - pos);
          set_per_level(stoul(post));
        }
    }
  else /* pos == npos */
    {
      set_per_level(0);
      set_value(stoi(input));
    }
}
