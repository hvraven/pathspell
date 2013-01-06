#include "output.h"
#include "options.h"
#include <iostream>
#include <regex>
#include <sstream>

using namespace std;

std::string
format_width(const std::string& input, size_t width)
{
  std::string output;
  std::ostringstream ss;
  ss << "([^\\n]{1," << width << "})(\\s+|$)";
  const regex linebreak(ss.str());
  return std::regex_replace(input, linebreak, "$1\n");
}

std::string
transform_format(std::string input)
{
  const static regex newline1("<p>(.*?)</p>");
  const static regex newline2("<br>");
  const static regex bold("<([bi])>(.+?)</\\1>");
  const static regex trash("</?[bip]>");

  const string format1 = regex_replace(input, newline1, "$1\n");
  const string format2 = regex_replace(input, newline2, "\n");
  const string format3 = regex_replace(format1, bold, "\033[1m$2\033[0m");
  const string format4 = regex_replace(format2, trash, "");
  return format4;
}

inline std::string
h1(const std::string& input)
{
  return "\033[1m" + input + "\033[0m";
}

inline std::string
h3(const std::string& input)
{
  return "\033[1m" + input + "\033[0m";
}

void
print_spell(const spell_type& spell)
{
  switch (options.output_type)
    {
    case output_type::full:
      {
        std::ostringstream out;
        out << " == "  << h1(spell.find("name")->second) << "\033[0m ==" << std::endl;

        out << h3("School: ") << spell.find("school")->second;
        if (spell.find("subschool")->second != std::string())
          out << "[" << spell.find("subschool")->second << "]";
        out << h3("  Level: ") << spell.find("spell_level")->second;
        if (spell.find("domain")->second != "NULL")
          out << h3("  Domain: ") << spell.find("domain")->second;
        out << std::endl;

        out << h3("Casting Time: ") << spell.find("casting_time")->second
            << h3("  Components: ") << spell.find("components")->second
            << std::endl;

        out << h3("Range: ") << spell.find("range")->second;
        if (spell.find("area")->second != std::string())
          out << h3("  Area: ") << spell.find("area")->second;
        if (spell.find("effect")->second != std::string())
          out << h3("  Effect: ") << spell.find("effect")->second;
        if (spell.find("targets")->second != std::string())
          out << h3("  Targets: ") << spell.find("targets")->second;
        if (spell.find("duration")->second != "NULL")
          out << h3("  Duration: ") << spell.find("duration")->second;
        out << std::endl;


        out << h3("Saving Throw: ");
        if (spell.find("saving_throw")->second != string())
          out << spell.find("saving_throw")->second;
        else
          out << "none";

        out << h3("  Spell Resistence: ");
        if (spell.find("spell_resistance")->second != string())
          out <<  spell.find("spell_resistence")->second << endl;
        else
          out << "no" << endl;

        const size_t width = 75;
        std::cout << std::endl
                  << format_width(out.str(), width)
                  << std::endl;

        std::cout << format_width(transform_format(spell.find("description_formated")->second),
                                  width)
                  << std::endl;

        break;

      }
    case output_type::list:
      {
        std::cout << spell.find("name")->second << std::endl;
        break;
      }
    }
}

