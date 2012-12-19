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
  static std::regex trash("</?[ip]+>");

  return std::regex_replace(std::regex_replace(input, newline, "\n"),
                            trash, "");
}

void
print_spell(std::map<std::string, std::string>& spell)
{
  switch (options.output_type)
    {
    case output_type::full:
      {
        std::ostringstream out;
        out << " == "  << spell["name"] << " ==" << std::endl;

        out << "School: " << spell["school"];
        if (spell["subschool"] != std::string())
          out << "[" << spell["subschool"] << "]";
        out << "  Level: " << spell["spell_level"];
        if (spell["domain"] != "NULL")
          out << "  Domain: " << spell["domain"];
        out << std::endl;

        out << "Casting Time: " << spell["casting_time"]
            << "  Components: " << spell["components"]
            << std::endl;

        out << "Range: " << spell["range"];
        if (spell["area"] != std::string())
          out << "  Area: " << spell["area"];
        if (spell["effect"] != std::string())
          out << "  Effect: " << spell["effect"];
        if (spell["targets"] != std::string())
          out << "  Targets: " << spell["targets"];
        if (spell["duration"] != "NULL")
          out << "  Duration: " << spell["duration"];
        out << std::endl;

        out << "Saving Throw: " << spell["saving_throw"]
            << "  Spell Resistence: " << spell["spell_resistence"]
            << std::endl;

        const size_t width = 72;
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

