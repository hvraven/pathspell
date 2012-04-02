#ifndef LIBRPG_XMLACCESS_H
#define LIBRPG_XMLACCESS_H

#include "elementlist.h"
#include "error.h"
#include "xml.h"
#include <string>
#include <unordered_map>

namespace RPG
{
  // iterator forward declarations
  template <class T>
  class Const_Xml_Access_Iterator;

  /**
   * @brief grants access to elements stored in an array
   * @todo add support for modifying xml file (insert, erase & encode)
   * @todo write de-/encoding functions for elements
   * @todo designed a cached version
   *
   * This class parses elements stored in XML-files and generetes the
   * corresponding classes from it.
   *
   * The genartion of this class opens the file and generates an index
   * of the files. The element from which the index shoud be created
   * could be given at class creation and defaults to "name".
   * Besides the index nothing is parsed until element
   * access. Espacialy no caching structure is present.
   *
   * The file stays open as long as the class instance exists.
   */
  template <class T>
  class Xml_Access
  {
  public:
    typedef T value_type;
    typedef unsigned int size_type;
    typedef Const_Xml_Access_Iterator<T> const_iterator;

    explicit Xml_Access(const std::string& file);
    Xml_Access(const std::string& file, const std::string& index);
    virtual ~Xml_Access();

    bool contains(const Identifier&) const;
    size_type size() const;

    value_type operator[](const Identifier&) const;

    const_iterator begin() const
      { return const_iterator(*this, index_.begin()); }
    const_iterator end() const
      { return const_iterator(*this, index_.end()); }

    void insert(const value_type&); /// @TODO
    void erase(const Identifier&);  /// @TODO

  protected:
    // these functions need to be specialized for the different elements
    value_type decode(const TiXmlElement *const) const;
    Identifier decode_index(const TiXmlElement *const) const;
    TiXmlElement encode(const T&) const;

  private:
    typedef std::unordered_map<Identifier, TiXmlElement*> Index_Map;
    const std::string file_;
    TiXmlDocument doc_;
    const std::string index_name_;
    Index_Map index_;

    friend class Const_Xml_Access_Iterator<T>;
  };

  template <class T>
  class Const_Xml_Access_Iterator
  {
    typedef std::unordered_map<Identifier, TiXmlElement*> Index_Map;
  public:
    Const_Xml_Access_Iterator<T>(const Xml_Access<T>& list,
                                 Index_Map::const_iterator list_it)
    : list_(list), list_it_(list_it) {}

    bool operator==(const Const_Xml_Access_Iterator<T>& it) const;
    bool operator!=(const Const_Xml_Access_Iterator<T>& it) const;
    typename Xml_Access<T>::value_type operator*() const;
    Const_Xml_Access_Iterator<T>& operator++();
    Const_Xml_Access_Iterator<T> operator++(int);

  private:
    const Xml_Access<T>& list_;
    Index_Map::const_iterator list_it_;
  };

  /***** Xml_Access ***********************************************/

  /**
   * @brief constructor with default index "name"
   * @param file path to the XML file to load
   */
  template <class T>
  Xml_Access<T>::Xml_Access(const std::string& file)
    : Xml_Access(file, "name")
  {}

  /**
   * @brief constructor with a given index
   * @param file path to the XML file to load
   * @param index index keywoard to use
   */
  template <class T>
  Xml_Access<T>::Xml_Access(const std::string& file, const std::string& index)
    : file_(file), index_name_(index)
  {
  }

  template <class T>
  Xml_Access<T>::~Xml_Access()
  {
  }

  /**
   * @brief checks if element exists in list
   * @param ident the index to look for
   */
  template <class T>
  inline bool
  Xml_Access<T>::contains(const Identifier& ident) const
  {
    return (index_[ident] != 0);
  }

  /**
   * @brief checked access to the elements
   * @param ident the identifier of the searched element
   * @throws xml_error if element is not found
   */
  template <class T>
  typename Xml_Access<T>::value_type
  Xml_Access<T>::operator[](const Identifier& ident) const
  {
    auto p = index_[ident];
    if (p)
      return decode(p);
    else
      throw xml_error("element " + ident + " not found");
  }

  /**
   * @brief returns the number of elements in the file
   */
  template <class T>
  inline typename Xml_Access<T>::size_type
  Xml_Access<T>::size() const
  {
    return index_.size();
  }

  /***** Const_Xml_Access_Iterator ***************************/

  template <class T>
  inline bool
  Const_Xml_Access_Iterator<T>::operator==
      (const Const_Xml_Access_Iterator<T>& it) const
  {
    return (list_it_ == it.list_it_);
  }

  template <class T>
  inline bool
  Const_Xml_Access_Iterator<T>::operator!=
      (const Const_Xml_Access_Iterator<T>& it) const
  {
    return (list_it_ != it.list_it_);
  }

  /**
   * @brief operator for derefercation. Creates a new T
   * @return a new generated T. Multiple dereferenction will generate multiple
   * instances of the corresponding object
   */
  template <class T>
  inline typename Xml_Access<T>::value_type
  Const_Xml_Access_Iterator<T>::operator*() const
  {
    return list_.decode(*list_it_);
  }

  template <class T>
  inline Const_Xml_Access_Iterator<T>&
  Const_Xml_Access_Iterator<T>::operator++()
  {
    ++list_it_;
    return *this;
  }

  template <class T>
  inline Const_Xml_Access_Iterator<T>
  Const_Xml_Access_Iterator<T>::operator++(int)
  {
    auto temp = clone *this;
    list_it_++;
    return temp;
  }

} /* namespace RPG */

#endif /* LIBRPG_XMLACCESS_H */
