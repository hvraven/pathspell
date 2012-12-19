#include "output.h"
#include "options.h"
#include "util.h"
#include <iostream>
#include <regex>

std::string
format_width(const std::string& input, size_t width)
{
  std::string output;
  auto it = begin(input);
  const std::string space(" ");
  for (size_t i = 0; i < input.size() / width; ++i)
    {
      auto next = std::find(it, it + width, '\n');
      // check if newline is in that line
      if (next != it + width)
        {
          output.insert(end(output), it, next);
          it = next;
        }

      next = find_last(it, it + width, ' ');
      output.insert(end(output), it, next);
      output.insert(end(output), '\n');
      it = next;
    }

  return output;
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
        std::cout << " == "  << spell["name"] << " ==" << std::endl;

        std::cout << "School: " << spell["school"];
        if (spell["subschool"] != std::string())
          std::cout << "[" << spell["subschool"] << "]";
        std::cout << "  Level: " << spell["spell_level"];
        if (spell["domain"] != "NULL")
          std::cout << "  Domain: " << spell["domain"];
        std::cout << std::endl;

        std::cout << "Casting Time: " << spell["casting_time"]
          << "  Components: " << spell["components"]
          << std::endl;

        std::cout << "Range: " << spell["range"];
        if (spell["area"] != std::string())
          std::cout << "  Area: " << spell["area"];
        if (spell["effect"] != std::string())
          std::cout << "  Effect: " << spell["effect"];
        if (spell["targets"] != std::string())
          std::cout << "  Targets: " << spell["targets"];
        if (spell["duration"] != "NULL")
          std::cout << "  Duration: " << spell["duration"];
        std::cout << std::endl;

        std::cout << "Saving Throw: " << spell["saving_throw"]
          << "  Spell Resistence: " << spell["spell_resistence"]
          << std::endl << std::endl;

        std::cout << format_width(transform_format(spell["description_formated"]),80) << std::endl;
        break;
      }
    case output_type::list:
      {
        std::cout << spell["name"] << std::endl;
        break;
      }
    }
}

