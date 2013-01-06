#ifndef SPELLS_CSV_H
#include <algorithm>
#include <fstream>
#include <map>
#include <limits>
#include <vector>
#include <string>

namespace CSV
{
  template <class T = std::vector<std::string>>
  class istream
  {
  public:
    typedef T           value_type;
    typedef value_type& reference_type;
    typedef value_type* pointer_type;

    istream(const std::string& file, int skip_lines = 0,
            char seperator = ',');

    istream& operator>>(reference_type vec)
      { vec = read_line(); return *this; }

    explicit operator bool() const { return (bool)input; }

    value_type read_line();

  private:
    std::ifstream input;
    const char seperator;
  };

  template <class T = std::vector<std::string>>
  class csv
  {
  public:
    using value_type = T;
    csv(const std::string& file, int skip_lines = 0, char seperator = ',');

  private:
    std::vector<value_type> entries;
  };

  template <class T = std::map<std::string, std::string>>
  class indexed_csv
  {
    using value_type = T;
    indexed_csv(const std::string& file, char seperator = ',');

  private:
    using storage_type = std::vector<value_type>;
    storage_type storage;
  };

  template <class T = std::map<std::string, std::string>>
  class indexed_stream
  {
  public:
    typedef T           value_type;
    typedef value_type& reference_type;
    typedef value_type* pointer_type;

    indexed_stream(const std::string& file, char seperator = ',');

    indexed_stream& operator>>(value_type& map)
      { map = read_line(); return *this; }
    explicit operator bool() const { return (bool)stream; }

    reference_type read_line();

  private:
    using index_type = std::vector<std::string>;
    istream<index_type> stream;
    index_type index;
    value_type line;
  };

  template <class T>
  istream<T>::istream(const std::string& file, int skip_lines, char seperator_)
       : input(file),
         seperator(seperator_)
  {
    for (; skip_lines > 0; --skip_lines)
      input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }

  template <class T>
  typename istream<T>::value_type
  istream<T>::read_line()
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

  template <class T>
  csv<T>::csv(const std::string& file, int skip_lines, char seperator)
       : entries()
  {
    istream<T> is(file, skip_lines, seperator);
    while (is)
      entries.push_back(is.read_line());
  }

  template <class T>
  indexed_csv<T>::indexed_csv(const std::string& file, char seperator)
       : storage{}
  {
    indexed_stream<T> is(file, seperator);
    while (is)
      storage.push_back(is.read_line());
  }

  template <class T>
  indexed_stream<T>::indexed_stream(const std::string& file,
                                    char seperator)
       : stream(file, 0, seperator),
         index(),
         line()
  {
    stream >> index;
  }

  template <class T>
  typename indexed_stream<T>::reference_type
  indexed_stream<T>::read_line()
  {
    index_type temp;
    line.clear();
    stream >> temp;
    temp.resize(index.size());
    for (size_t i = 0; i < std::min(index.size(), temp.size()); ++i)
      line.emplace(index[i], temp[i]);

    return line;
  }

}

#endif /* SPELL_CSV_H */
