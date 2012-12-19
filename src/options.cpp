#include "options.h"
#include <getopt.h>
#include <iostream>
using namespace std;

struct options options;

void
usage(std::ostream& s)
{
  s << "Usage: spells [options] [name]" << endl
    << "Options:" << endl
    << "  -c,--class    <opt>  list only spells with specified class" << endl
    << "  -d,--domain   <opt>  list only spells with specified domain" << endl
    << "  -l,--list-only       display only the names" << endl
    << "  -r,--range    <opt>  list only spells with specified range" << endl
    << "  -s,--school   <opt>  list only spells with specified school" << endl
    ;
}

options::options()
   : filter(),
     output_type(output_type::full)
{
}

void
options::parse_args(int argc, char** argv)
{
  const char opts[] = "c:d:hlr:s:";

  const struct option long_opts[] = {
    { "class" ,    required_argument, nullptr, 'c'},
    { "domain",    required_argument, nullptr, 'd'},
    { "list-only", no_argument,       reinterpret_cast<int*>(&output_type),
        static_cast<int>(output_type::list)},
    { "range",     required_argument, nullptr, 'r'},
    { "school",    required_argument, nullptr, 's'},
    { nullptr,     no_argument,       nullptr, 0  }
  };

  int long_index = 0;
  int opt = 0;
  while ((opt = getopt_long(argc, argv, opts, long_opts, &long_index)) != -1)
    switch (opt)
      {
      case 0:
        break;
      case 'c':
        filter.add_filter("spell_level", optarg);
        break;
      case 'd':
        filter.add_filter("domain", optarg);
        break;
      case 'h':
        usage(cout);
        exit(0);
        break;
      case 'l':
        output_type = output_type::list;
        break;
      case 'r':
        filter.add_filter("range", optarg);
        break;
      case 's':
        filter.add_filter("school", optarg);
        break;
      case '?':
        usage(cerr);
        exit(1);
        break;
      default:
        break;
      }

  for (int i = optind; i < argc; ++i)
    filter.add_filter("name", argv[i]);
}
