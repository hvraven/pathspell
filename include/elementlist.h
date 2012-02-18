#ifndef LIBRPG_ELEMENTLIST_H
#define LIBRPG_ELEMENTLIST_H

#include "element.h"
#include <iterator>
#include <memory>
#include <unordered_map>
#include <vector>

namespace RPG
{
  template <typename T>
  class Base_Element_List
  {
  public:
    typedef T value_type;
    typedef std::shared_ptr<T> pointer;
    typedef std::shared_ptr<const T> const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef std::iterator<std::bidirectional_iterator_tag,T> iterator;
    typedef std::iterator<std::bidirectional_iterator_tag,T> const_iterator;

    virtual bool contains(const Identifier&) const = 0;
    virtual int size() const = 0;

    virtual iterator find(const Identifier&) = 0;
    virtual const_iterator find(const Identifier&) const = 0;
    virtual reference operator[](const Identifier& identifier) = 0;

    virtual void insert(const T&) = 0;
    virtual void import(const Base_Element_List<T>&) = 0;
    virtual void erase(const Identifier&) = 0;
    virtual void clear() = 0;

  protected:
    virtual std::shared_ptr<T> get_element_ptr(const Identifier&) = 0;
    virtual std::shared_ptr<T> get_element_ptr(iterator) = 0;
    virtual std::vector<std::shared_ptr<T>> get_all_element_ptr() = 0;
  };

  template <typename T>
  class Element_List_Iterator;
  template <typename T>
  class Const_Element_List_Iterator;

  template <typename T>
  class Element_List : public Base_Element_List<T>
  {
  public:
    Element_List<T>();
    virtual ~Element_List<T>() {}

    typedef Element_List_Iterator<T> iterator;
    typedef Const_Element_List_Iterator<T> const_iterator;
    typedef T value_type;
    typedef std::shared_ptr<T> pointer;
    typedef std::shared_ptr<const T> const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef std::unordered_map<Identifier, pointer> Element_Map;

    bool contains(const Identifier&) const override;
    int size() const override;

    iterator find(const Identifier&) override;
    const_iterator find(const Identifier&) const override;
    reference operator[](const Identifier& identifier) override;
    pointer find_ptr(const Identifier&);
    const_pointer find_ptr(const Identifier&) const;

    void insert(const T&) override;
    void import(const Base_Element_List<T>&) override;
    void erase(const Identifier&) override;
    void clear() override;

    iterator begin() { return iterator(*this, 0); }
    const_iterator begin() const { return const_iterator(*this, 0); }
    iterator end() { return iterator(*this, size()); }
    const_iterator end() const { return const_iterator(*this, size()); }

  protected:
    std::shared_ptr<T> get_element_ptr(const Identifier& identifier) override
      { return elements_[identifier]; }
    std::shared_ptr<T> get_element_ptr(iterator it) override;
      { return *(it.list_it_); }

  private:
    friend class Element_List_Iterator<T>;
    friend class Const_Element_List_Iterator<T>;

    Element_Map elements_;
  };

  template <typename T>
  class Element_List_Iterator : public Base_Element_List<T>::iterator
  {
  public:
    Element_List_Iterator(Element_List<T>& list, int position)
      : list_(list), list_it_(list_.elements_.begin() + position) {}

    bool operator==(const Element_List_Iterator<T>& it) const
      { return list_it_ == it.list_it_; }
    bool operator!=(const Element_List_Iterator<T>& it) const
      { return !(*this == it); }
    typename Element_List<T>::reference operator*() { return *list_it_; }
    typename Element_List<T>::pointer operator->() { return list_it_; }
    Element_List_Iterator<T>& operator++() { list_it_++; return *this; }
    Element_List_Iterator<T> operator++(int);
    Element_List_Iterator<T>& operator--() { list_it_--; return *this; }
    Element_List_Iterator<T> operator--(int);

  private:
    Element_List<T>& list_;
    typename Element_List<T>::Element_Map::iterator list_it_;
  };

  template <typename T>
  class Const_Element_List_Iterator
      : public Base_Element_List<T>::const_iterator
  {
  public:
    Const_Element_List_Iterator(const Element_List<T>& list, int position)
      : list_(list), list_it_(list_.elements_.begin() + position) {}

    bool operator==(const Const_Element_List_Iterator<T>& it) const
      { return list_it_ == it.list_it_; }
    bool operator!=(const Const_Element_List_Iterator<T>& it) const
      { return !(*this == it); }
    typename Element_List<T>::const_reference operator*() const 
      { return *list_it_; }
    typename Element_List<T>::const_pointer operator->() const
      { return list_it_; }
    Const_Element_List_Iterator<T>& operator++() { list_it_++; return *this; }
    Const_Element_List_Iterator<T> operator++(int);
    Const_Element_List_Iterator<T>& operator--() { list_it_--; return *this; }
    Const_Element_List_Iterator<T> operator--(int);

  private:
    const Element_List<T>& list_;
    typename Element_List<T>::Element_Map::const_iterator list_it_;
  };

  /**** Element_List ************************************************/

  /**** Element_List_Iterator ***************************************/

  template <typename T>
  Element_List_Iterator<T>
  Element_List_Iterator<T>::operator++(int)
  {
    Element_List_Iterator<T> temp = clone *this;
    list_it_++;
    return temp;
  }

  template <typename T>
  Element_List_Iterator<T>
  Element_List_Iterator<T>::operator--(int)
  {
    Element_List_Iterator<T> temp = clone *this;
    list_it_--;
    return temp;
  }

  /**** Const_Element_List_Iterator *********************************/

  template <typename T>
  Const_Element_List_Iterator<T>
  Const_Element_List_Iterator<T>::operator++(int)
  {
    Const_Element_List_Iterator<T> temp = clone *this;
    list_it_++;
    return temp;
  }

  template <typename T>
  Const_Element_List_Iterator<T>
  Const_Element_List_Iterator<T>::operator--(int)
  {
    Const_Element_List_Iterator<T> temp = clone *this;
    list_it_--;
    return temp;
  }

} /* namespace RPG */
#endif /* LIBRPG_ELEMENTLIST_H */
