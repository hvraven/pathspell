#include "output.h"
#include "options.h"
#include <iostream>
#include <regex>
#include <sstream>

std::string
format_width(const std::string& input, size_t width)
{
  std::string output;
  std::ostringstream ss;
  ss << "([^\\n]{1," << width << "})\\s+";
  std::regex linebreak(ss.str());
  return std::regex_replace(input, linebreak, "$1\n");
}

std::string
transform_format(std::string input)
{
  static std::regex newline("</p>\\s*<p>");
  static std::regex trash("</?[bip]+>");

  return std::regex_replace(std::regex_replace(input, newline, "\n"),
                            trash, "");
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
print_spell(std::map<std::string, std::string>& spell)
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

        out << h3("Saving Throw: ") << spell["saving_throw"]
            << h3("  Spell Resistence: ") << spell["spell_resistence"]
            << std::endl;

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

