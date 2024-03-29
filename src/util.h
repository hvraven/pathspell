#ifndef PF_UTIL_H
#define PF_UTIL_H

#include <algorithm>
#include <memory>
#include <numeric>
#include <regex>
#include <string>
#include <vector>

template<typename T, typename... Args>
constexpr
std::unique_ptr<T>
make_unique(Args&&... args)
{
  return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

template <typename It, typename T>
std::string
join(It first, It last, T seperator)
{
  if (first == last)
    return std::string{};

  const std::string start{*first};
  return std::accumulate(++first, last, start,
    [=](std::string& acc, const std::string& e)
      { return acc += seperator + e; });
}

template <typename Container = std::vector<std::string>>
Container
split(const std::string& in, const std::string& seperator = "\\s+")
{
  const std::regex rgx{seperator};
  Container out;
  std::copy(std::sregex_token_iterator{begin(in), end(in), rgx, -1},
            std::sregex_token_iterator{},
            std::back_inserter(out));
  return out;
}

std::string to_lower(std::string);

#endif /* PF_UTIL_H */
