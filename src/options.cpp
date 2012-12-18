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
    << "  -l,--list-only       list only the names" << endl;
}

options::options()
   : filter(),
     output_type(output_type::full)
{
}

void
options::parse_args(int argc, char** argv)
{
  const char opts[] = "c:d:hl";

  const struct option long_opts[] = {
    { "class" ,    required_argument, nullptr,      'c'              },
    { "domain",    required_argument, nullptr,      'd'              },
    { "list-only", no_argument,       reinterpret_cast<int*>(&output_type),
        static_cast<int>(output_type::list)},
    { nullptr,     no_argument,       nullptr,      0                }
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
      case '?':
        usage(cerr);
        exit(1);
        break;
      default:
        break;
      }

  if (optind < argc)
    filter.add_filter("name", argv[optind]);

  for (int i = optind + 1; i < argc; ++i)
    cerr << "Warning: Unused parameter \"" << argv[i] << "\"" << endl;
}
