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
  class Xml_Element_List_Iterator;
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
    void clear_index() { index_valid_ = false; index_.clear(); }
    bool index_is_valid() { return index_valid_; }

    bool contains(const Identifier&) const;
    int size() const;

    T get_element(const Identifier&) const;
    std::vector<T> get_elements() const;

    virtual const_iterator find(const Identifier&) const;
    virtual reference operator[](const Identifier& identifier) = delete;

    const_iterator begin() const;
    const_iterator end() const;

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
    bool index_valid_;

    virtual std::shared_ptr<T> get_element_ptr(const Identifier&);
    virtual std::shared_ptr<T> get_element_ptr(const_iterator);
    virtual std::vector<std::shared_ptr<T>> get_all_element_ptr();

    virtual T decode(const TiXmlElement*) const = 0;
    virtual T decode_index(const TiXmlElement*) const;
    virtual TiXmlElement encode(const T&) const = 0;
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

    index_valid_ = true;
  }

  /**
   * @brief check if element exists in file
   * @param identifier the element to search for
   */
  template <typename T>
  bool
  Xml_Element_List<T>::contains(const Identifier& identifier) const
  {
    if (index_valid_ = true)
      return index_[identifier];
    else
      {
        for (TiXmlElement const* pelement
               = doc_.FirstChildElement()->FirstChildElement();
             pelement; pelement = pelement->NextSiblingElement())
          if (decode_index(pelement) == identifier)
            return true;
        return false;
      }
  }

  /**
   * @brief returns the number of elements in the file
   */
  template <typename T>
  int
  Xml_Element_List<T>::size() const
  {
    if (index_valid_ = true)
      return index_.size();
    else
      {
        int i = 0;
        for (TiXmlElement* pelement
               = doc_.FirstChildElement()->FirstChildElement();
             pelement; pelement = pelement->NextSiblingElement())
          i++;
        return i;
      }
  }

  /**
   * @brief returns a instance of the serched object
   * @throws std::invalid_argument if element is not found
   */
  template <typename T>
  T
  Xml_Element_List<T>::get_element(const Identifier& identifier) const
  {
    if (index_valid_)
      {
        Index_Map::const_iterator it = index_.find(identifier);
        if (it == index_.end())
          throw std::invalid_argument(identifier + " not in list");

        return *it;
      }
    else
      {
        for (TiXmlElement* pelement
               = doc_.FirstChildElement()->FirstChildElement();
             pelement; pelement = pelement->NextSiblingElement())
          if (decode_index(pelement) == identifier)
            return decode(pelement);

        throw std::invalid_argument(identifier + " not in list");
      }
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

  /**
   * @brief generates a shared_ptr with a new object in it
   * @return the generated element. Each time this function is called a new
   * shared pointer will be generated.
   */
  template <typename T>
  std::shared_ptr<T>
  Xml_Element_List<T>::get_element_ptr(const Identifier& identifier)
  {
    TiXmlElement* pelement;
    if (index_valid_)
      pelement = index_[identifier];
    else
      for (pelement = doc_.FirstChildElement()->FirstChildElement();
           pelement; pelement = pelement->NextSiblingElement())
        if (decode_index(pelement) == identifier)
          break;

    return std::shared_ptr<T>(new T(decode(pelement)));
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

} /* namespace RPG */

#endif /* LIBRPG_XMLACCESS_H */
