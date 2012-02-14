#ifndef LIBRPG_ACCESS_H
#define LIBRPG_ACCESS_H

#include "element.h"
#include <memory>
#include <unordered_map>
#include <vector>

namespace RPG
{

  /**
   * @brief generic class for storing elements
   *
   * This class stores elements of a certain type.
   * It is not made for direct acces of functions. It is only the storage,
   * keeping the elements for p.e. list classes, which give (un)sorted, or
   * filtered access to these elements.
   * If you just want to access these elements as are use a Element_List.
   */
  template <typename T = Element>
  class Access
  {
    typedef std::unordered_map<Identifier, std::shared_ptr<T>> Element_Map;
  public:
    Access<T>() {};
    virtual ~Access<T>() {}

    virtual bool has_element(const Identifier&) const;
    virtual int number_of_elements() const { return elements_.length(); }
    virtual std::shared_ptr<T> get_element(const Identifier& identifier)
      { return elements_[identifier]; }

    virtual void import_elements(const Access<T>&);
    virtual std::vector<T> export_elements() const;

    virtual void add_element(const T&);

    virtual std::shared_ptr<T> operator[](const Identifier& identifier)
      { return elements_[identifier]; }

    typedef typename Element_Map::iterator iterator;
    typedef typename Element_Map::const_iterator const_iterator;
    //typedef ptrdiff_t difference_type;
    typedef size_t size_type;
    typedef std::shared_ptr<T> value_type;
    typedef std::shared_ptr<T>* pointer;
    typedef std::shared_ptr<T>& reference;

    iterator begin() { return elements_.begin(); }
    iterator end() { return elements_.end(); }

  private:
    Element_Map elements_;
  };

  /**** Access ******************************************************/

  /**
   * @brief checks if a element with given identifier exists in Access
   * @param identifier element to search for
   * @return true if element is found
   */
  template <typename T>
  bool
  Access<T>::has_element(const Identifier& identifier) const
  {
      return (elements_.find(identifier) != elements_.end());
  }

  template <typename T>
  void
  Access<T>::import_elements(const Access<T>& import)
  {
    for (typename Access<T>::const_iterator it = import.begin();
         it != import.end(); it++)
      elements_[it->first].reset(it->second);
  }

  template <typename T>
  std::vector<T>
  Access<T>::export_elements() const
  {
    std::vector<T> result;
    for (typename Access<T>::const_iterator it = this->begin();
         it != this->end(); it++)
      result.push_back(*it);
    return result;
  }

  template <typename T>
  void
  Access<T>::add_element(const T& element)
  {
    (*this)[element.get_identifier()].reset(element);
  }

}

#endif /* LIBRPG_ACCESS_H */
