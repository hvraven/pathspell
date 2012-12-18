#ifndef SPELLS_CSV_H
#define SPELLS_CSV_H

#include <fstream>
#include <map>
#include <vector>
#include <string>

namespace CSV
{
  class istream
  {
  public:
    typedef std::vector<std::string>  value_type;
    typedef const value_type&         reference_type;
    typedef const value_type*         pointer_type;

    istream(const std::string& file, int skip_lines = 0,
                    char seperator = ',');

    istream& operator>>(std::vector<std::string>& vec)
      { vec = read_line(); return *this; }

    explicit operator bool() const { return (bool)input; }

    value_type read_line();

  private:
    std::ifstream input;
    const char seperator;
  };

  class csv
  {
  public:
    csv(const std::string& file, int skip_lines = 0, char seperator = ',');

    class iterator
    {
    public:
      typedef std::vector<std::vector<std::string>>::iterator::iterator_category
        iterator_category;
    };

  private:
    std::vector<std::vector<std::string>> entries;
  };

  class indexed_stream
  {
  public:
    typedef std::map<std::string, std::string> value_type;
    typedef value_type&                        reference_type;
    typedef value_type*                        pointer_type;

    indexed_stream(const std::string& file, char seperator = ',');

    indexed_stream& operator>>(value_type& map)
      { map = read_line(); return *this; }
    explicit operator bool() const { return (bool)stream; }

    reference_type read_line();

  private:
    istream stream;
    std::vector<std::string> index;
    std::map<std::string, std::string> line;
  };

}

#endif /* SPELL_CSV_H */
