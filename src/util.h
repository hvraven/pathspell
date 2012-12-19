#ifndef PF_UTIL_H
#define PF_UTIL_H

template <typename It, typename T>
It
find_last(It first, It last, const T& value)
{
  for (; first != last; ++first)
    {
      auto next = std::find(first, last, value);
      if (next == last)
        return first;
      first = next;
    }

  return last;
}

#endif /* PF_UTIL_H */
