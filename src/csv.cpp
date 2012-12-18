#include "csv.h"
#include <algorithm>
#include <assert.h>
#include <limits>

using namespace CSV;

istream::istream(const std::string& file, int skip_lines, char seperator_)
     : input(file),
       seperator(seperator_)
{
  for (; skip_lines > 0; --skip_lines)
    input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

istream::value_type
istream::read_line()
{
  std::string line;
  std::getline(input, line);

  std::vector<std::string> output;

  for (auto it = begin(line);; ++it)
    {
      auto next = find(it, end(line), seperator);
      output.push_back(std::string(it, next));

      if (next == end(line))
        return output;

      it = next;
    }

  return output;
}

csv::csv(const std::string& file, int skip_lines, char seperator)
     : entries()
{
  istream is(file, skip_lines, seperator);
  while (is)
    entries.push_back(is.read_line());
}

indexed_stream::indexed_stream(const std::string& file,
                                                 char seperator)
     : stream(file, 0, seperator),
       index(),
       line()
{
  stream >> index;
}

indexed_stream::reference_type
indexed_stream::read_line()
{
  std::vector<std::string> temp;
  line.clear();
  stream >> temp;
  temp.resize(index.size());
  assert(index.size() >= temp.size());
  transform(begin(index), end(index), begin(temp), inserter(line, end(line)),
            [](const std::string& a, const std::string& b)
              { return make_pair(a, b); });

  return line;
}

