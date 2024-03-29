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
        out << " == "  << h1(spell["name"]) << "\033[0m ==" << std::endl;

        out << h3("School: ") << spell["school"];
        if (spell["subschool"] != std::string())
          out << "[" << spell["subschool"] << "]";
        out << h3("  Level: ") << spell["spell_level"];
        if (spell["domain"] != "NULL")
          out << h3("  Domain: ") << spell["domain"];
        out << std::endl;

        out << h3("Casting Time: ") << spell["casting_time"]
            << h3("  Components: ") << spell["components"]
            << std::endl;

        out << h3("Range: ") << spell["range"];
        if (spell["area"] != std::string())
          out << h3("  Area: ") << spell["area"];
        if (spell["effect"] != std::string())
          out << h3("  Effect: ") << spell["effect"];
        if (spell["targets"] != std::string())
          out << h3("  Targets: ") << spell["targets"];
        if (spell["duration"] != "NULL")
          out << h3("  Duration: ") << spell["duration"];
        out << std::endl;


        out << h3("Saving Throw: ");
        if (spell["saving_throw"] != string())
          out << spell["saving_throw"];
        else
          out << "none";

        out << h3("  Spell Resistence: ");
        if (spell["spell_resistance"] != string())
          out <<  spell["spell_resistence"] << endl;
        else
          out << "no" << endl;

        const size_t width = 75;
        std::cout << std::endl
                  << format_width(out.str(), width)
                  << std::endl;

        std::cout << format_width(transform_format(spell["description_formated"]),
                                  width)
                  << std::endl;

        break;

      }
    case output_type::list:
      {
        std::cout << spell["name"] << std::endl;
        break;
      }
    }
}

