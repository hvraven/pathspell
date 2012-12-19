#ifndef PF_UTIL_H
#define PF_UTIL_H

template <typename It, typename T>
std::string
join(It first, It last, T seperator)
{
  if (first == last)
    return std::string();

  std::string output{*first};
  for (++first; first != last; ++first)
    {
      output += seperator;
      output += *first;
    }
  return output;
}

#endif /* PF_UTIL_H */
