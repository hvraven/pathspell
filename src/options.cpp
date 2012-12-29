#include "options.h"
#include "util.h"
#include <getopt.h>
#include <iostream>
#include <regex>
using namespace std;

struct options options;

void   usage(ostream& s);
bool   level_argument_ok(const string& input);
string expand_class_filter(const std::string& input);
string parse_level_filter(const std::string&);

options::options()
   : filter{},
     output_type{output_type::full},
     exact_match{false}
{
}

void
options::parse_args(int argc, char** argv)
{
  const char opts[] = "c:d:ehil:r:s:";

  const struct option long_opts[] = {
    { "class" ,      required_argument, nullptr, 'c'},
    { "domain",      required_argument, nullptr, 'd'},
    { "exact",       no_argument,       reinterpret_cast<int*>(&exact_match), 1},
    { "help",        no_argument,       nullptr, 'h'},
    { "interactive", no_argument,       reinterpret_cast<int*>(&interactive), 1},
    { "level",       required_argument, nullptr, 'l'},
    { "list-only",   no_argument,       reinterpret_cast<int*>(&output_type),
        static_cast<int>(output_type::list)},
    { "range",       required_argument, nullptr, 'r'},
    { "school",      required_argument, nullptr, 's'},
    { nullptr,       no_argument,       nullptr, 0  }
  };

  int long_index = 0;
  int opt = 0;
  string tmp_class;
  string tmp_level;
  while ((opt = getopt_long(argc, argv, opts, long_opts, &long_index)) != -1)
    switch (opt)
      {
      case 0:
        break;
      case 'c':
        tmp_class = optarg;
        break;
      case 'd':
        filter.add_filter<regex_filter>("domain", optarg);
        break;
      case 'e':
        exact_match = true;
        break;
      case 'h':
        usage(cout);
        exit(0);
        break;
      case 'i':
        interactive = true;
        break;
      case 'l':
        if (! level_argument_ok(optarg))
          {
            std::cerr << "Error while parsing command line: Invalid level limit." << endl
                      << "Possible options:" << endl
                      << "  digit         only that level" << endl
                      << "  -digit        all levels <= that level" << endl
                      << "  +digit        all levels >= that level" << endl
                      << "  digit-digit   levels in that range" << endl;
            exit(1);
          }
        tmp_level = optarg;
        break;
      case 'r':
        filter.add_filter<regex_filter>("range", optarg);
        break;
      case 's':
        filter.add_filter<regex_filter>("school", optarg);
        break;
      case '?':
        usage(cerr);
        exit(1);
        break;
      default:
        break;
      }

  if (tmp_class != string())
    {
      if (tmp_level != string())
        filter.add_filter<regex_filter>
          ("spell_level", expand_class_filter(tmp_class) + " " +
                          parse_level_filter(tmp_level));
      else
        filter.add_filter<regex_filter>("spell_level", tmp_class);
    }
  else
    if (tmp_level != string())
      filter.add_filter<regex_filter>("spell_level", parse_level_filter(tmp_level));

  if (exact_match)
    {
      filter.add_filter<exact_regex_filter>
        ("name", join(argv + optind, argv + argc, ' '));
    }
  else
    for (int i = optind; i < argc; ++i)
      filter.add_filter<regex_filter>("name", argv[i]);
}

void
usage(std::ostream& s)
{
  s << "Usage: spells [options] [name]" << endl
    << "Options:" << endl
    << "  -c,--class    <opt>  list only spells with specified class" << endl
    << "  -d,--domain   <opt>  list only spells with specified domain" << endl
    << "  -e,--excact          display only spells with exact name match" << endl
    << "  -h,--help            print this message" << endl
    << "  -l --level           limit to spells with the matching spell levels" << endl
    << "     --list-only       display only the names" << endl
    << "  -r,--range    <opt>  list only spells with specified range" << endl
    << "  -s,--school   <opt>  list only spells with specified school" << endl
    ;
}

bool
level_argument_ok(const string& input)
{
  const regex rgx{"(\\d-|[-+])?\\d"};
  return regex_match(input, rgx);
}

string
expand_class_filter(const string& input)
{
  return "([[:alpha:]]+/)?" + input + "(/[[:alpha:]]+)?";
}

string
parse_level_filter(const string& input)
{
  const regex leq{"^-(\\d)"};
  const regex geq{"^\\+(\\d)"};
  string output{regex_replace(input, leq, "1-$1")};
  output = regex_replace(output, geq, "$1-9");
  return "[" + output + "]";
}
