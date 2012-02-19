#ifndef LIBRPG_XMLACCESS_H
#define LIBRPG_XMLACCESS_H

#define TIXML_USE_STL

#include "elementlist.h"
#include <stdexcept>
#include <string>
#include <tinyxml.h>
#include <unordered_map>
#include <vector>

namespace RPG
{
	typedef std::string filetype;

  template <typename T>
  class Const_Xml_Element_List_Iterator;

  template <typename T>
	class Xml_Element_List : public RPG::Base_Element_List<T>
	{
	public:
		Xml_Element_List(const filetype& file, const std::string& index = "name");
		virtual ~Xml_Element_List();

    typedef T value_type;
    typedef std::shared_ptr<T> pointer;
    typedef std::shared_ptr<const T> const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef Const_Xml_Element_List_Iterator<T> const_iterator;

    void set_file(const filetype& file);
    void load_file(const filetype& file);

    void generate_index();

    bool contains(const Identifier&) const;
    int size() const;

    T get_element(const Identifier&) const;
    std::vector<T> get_elements() const;

    /// @todo find out if there is a way for the correct return value
    typename Base_Element_List<T>::const_iterator find(const Identifier&) const;
    //virtual reference operator[](const Identifier& identifier) = delete;

    const_iterator begin() const 
      { return const_iterator(*this, index_.begin()); }
    const_iterator end() const
      { return const_iterator(*this, index_.end()); }

    virtual void insert(const T&);
    virtual void import(const Base_Element_List<T>&);
    virtual void erase(const Identifier&);
    virtual void clear();

	protected:
    typedef std::unordered_map<Identifier, TiXmlElement*> Index_Map;
		const filetype file_path_;
		TiXmlDocument doc_;
    std::string index_name_;
    Index_Map index_;

    virtual std::shared_ptr<T> get_element_ptr(const Identifier&);
    virtual std::shared_ptr<T> get_element_ptr(const_iterator);
    virtual std::vector<std::shared_ptr<T>> get_all_element_ptr();

    virtual T decode(const TiXmlElement *const) const = 0;
    virtual Identifier decode_index(const TiXmlElement *const) const;
    virtual TiXmlElement encode(const T&) const = 0;

    friend class Const_Xml_Element_List_Iterator<T>;
	};

  template <typename T>
  class Const_Xml_Element_List_Iterator
      : public RPG::Base_Element_List<T>::const_iterator
  {
  public:
    Const_Xml_Element_List_Iterator<T>(const Xml_Element_List<T>& list,
        std::unordered_map<Identifier, TiXmlElement*>::const_iterator list_it)
      : list_(list), list_it_(list_it) {}

    bool operator==(const Const_Xml_Element_List_Iterator<T>& it) const
      { return list_it_ = it.list_it_; }
    bool operator!=(const Const_Xml_Element_List_Iterator<T>& it) const
      { return !(*this == it); }
    typename Xml_Element_List<T>::value_type operator*() const;
    typename Xml_Element_List<T>::pointer operator->() const
      { return std::shared_ptr<T>(new T(**this)); }
    Const_Xml_Element_List_Iterator<T>& operator++()
      { ++list_it_; return *this; }
    Const_Xml_Element_List_Iterator<T> operator++(int);

  private:
    const Xml_Element_List<T>& list_;
    std::unordered_map<Identifier, TiXmlElement*>::const_iterator list_it_;
  };

  /***** Xml_Element_List ******************************************/

  /**
   * @brief tries to set the connected file
   * @param file path to the new file
   * @throws std::invalid_argument if file could not be loaded
   *
   * if an error occures nothing is changed
   */
  template <typename T>
  void
  Xml_Element_List<T>::set_file(const filetype& file)
  {
    doc_ = file;
    if ( ! doc_.LoadFile() )
      {
        doc_ = file_path_;
        throw std::invalid_argument("could not load " + file);
      }

    file_path_ = file;
  }

  /**
   * @brief sets the connected file and generates a new index
   * @param file path to the file to load
   * @throws std::invalid_argument if file could not be loaded
   *
   * this function works like set_file(), but (re)generates the index
   * if an error occures nothing is changed
   */
  template <typename T>
  void
  Xml_Element_List<T>::load_file(const filetype& file)
  {
    set_file(file);
    generate_index();
  }

  /**
   * @brief generates an index for the given file
   *
   * this function generates an index of all elements in the file.
   * This allows a faster access to specific elements, since no search in the
   * file is necessary.
   */
  template <typename T>
  void
  Xml_Element_List<T>::generate_index()
  {
    index_.clear();

    for (TiXmlElement* pelement
           = doc_.FirstChildElement()->FirstChildElement();
         pelement; pelement = pelement->NextSiblingElement())
      index_[decode_index(pelement)] = pelement;
  }

  /**
   * @brief check if element exists in file
   * @param identifier the element to search for
   */
  template <typename T>
  bool
  Xml_Element_List<T>::contains(const Identifier& identifier) const
  {
    return (index_.find(identifier) != index_.end());
  }

  /**
   * @brief returns the number of elements in the file
   */
  template <typename T>
  int
  Xml_Element_List<T>::size() const
  {
    return index_.size();
  }

  /**
   * @brief returns a instance of the serched object
   * @throws std::invalid_argument if element is not found
   */
  template <typename T>
  T
  Xml_Element_List<T>::get_element(const Identifier& identifier) const
  {
    Index_Map::const_iterator it = index_.find(identifier);
    if (it == index_.end())
      throw std::invalid_argument(identifier + " not in list");

    return *it;
  }

  /**
   * @brief returns all elements in the file
   *
   * this function reads the complete file, generates objects for them
   * and returns them all.
   * This function is independet from the index.
   */
  template <typename T>
  std::vector<T>
  Xml_Element_List<T>::get_elements() const
  {
    std::vector<T> result;

    for (TiXmlElement* pelement
           = doc_.FirstChildElement()->FirstChildElement();
         pelement; pelement = pelement->NextSiblingElement())
      result.push_back(decode(pelement));

    return result;
  }

  template <typename T>
  typename Base_Element_List<T>::const_iterator
  Xml_Element_List<T>::find(const Identifier& identifier) const
  {
    return Const_Xml_Element_List_Iterator<T>((*this), index_.find(identifier));
  }

  /**
   * @brief generates a shared_ptr with a new object in it
   * @return the generated element. Each time this function is called a new
   * shared pointer will be generated.
   */
  template <typename T>
  std::shared_ptr<T>
  Xml_Element_List<T>::get_element_ptr(const Identifier& identifier)
  {
    return std::shared_ptr<T>(new T(decode(index_[identifier])));
  }

  /**
   * @brief generates shared_ptrs for all objects in the file
   */
  template <typename T>
  std::vector<std::shared_ptr<T>>
  Xml_Element_List<T>::get_all_element_ptr()
  {
    std::vector<std::shared_ptr<T>> result;

    for (TiXmlElement* pelement
           = doc_.FirstChildElement()->FirstChildElement();
         pelement; pelement = pelement->NextSiblingElement())
      result.push_back(std::shared_ptr<T>(new T(decode(pelement))));

    return result;
  }

  /***** Const_Xml_Element_List_Iterator ***************************/

  /**
   * @brief operator for derefercation. Creates a new T
   * @return a new generated T. Multiple dereferenction will generate multiple
   * instances of the corresponding object
   */
  template <typename T>
  typename Xml_Element_List<T>::value_type
  Const_Xml_Element_List_Iterator<T>::operator*() const
  {
    return list_.decode(*list_it_);
  }

  template <typename T>
  Const_Xml_Element_List_Iterator<T>
  Const_Xml_Element_List_Iterator<T>::operator++(int)
  {
    auto temp = clone *this;
    list_it_++;
    return temp;
  }

} /* namespace RPG */

#endif /* LIBRPG_XMLACCESS_H */
