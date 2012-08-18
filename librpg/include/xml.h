#ifndef LIBRPG_XML_H
#define LIBRPG_XML_H 1

#define TIXML_USE_STL
#include <tinyxml.h>

/**
 * @brief Iterator adapter class for TiXmlElement*
 *
 * this class builds an bi-directional iterator arround an TiXmlElement*
 * it iterates over all child elements of the given pointer.
 */
class Xml_Iterator
{
public:
  Xml_Iterator(TiXmlElement* p)
  : p_(p) {}

  bool operator==(const Xml_Iterator it) const { return p_ == it.p_; }
  bool operator!=(const Xml_Iterator it) const { return !(*this == it); }
  TiXmlElement& operator*() { return *p_; }
  Xml_Iterator& operator++() { p_->NextSiblingElement(); return *this; }
  Xml_Iterator operator++(int);
  Xml_Iterator& operator--()
    { p_->PreviousSibling()->ToElement(); return *this; }
  Xml_Iterator operator--(int);

private:
  TiXmlElement* p_;
};

/**
 * @brief Const iterator adapter class for TiXmlElement*
 * @see Xml_Iterator
 */
class Const_Xml_Iterator
{
public:
  Const_Xml_Iterator(const TiXmlElement* p)
  : p_(p) {}

  bool operator==(const Const_Xml_Iterator it) const {return p_ == it.p_; }
  bool operator!=(const Const_Xml_Iterator it) const {return !(*this == it); }
  const TiXmlElement& operator*() const { return *p_; }
  Const_Xml_Iterator& operator++() { p_->NextSiblingElement(); return *this; }
  Const_Xml_Iterator operator++(int);
  Const_Xml_Iterator& operator--()
   { p_->PreviousSibling()->ToElement(); return *this; }
  Const_Xml_Iterator operator--(int);

private:
  const TiXmlElement* p_;
};

inline Xml_Iterator
begin(TiXmlElement* p)
{ return Xml_Iterator(p->FirstChildElement()); }

inline Xml_Iterator
end(TiXmlElement*)
{ return Xml_Iterator(nullptr); }

inline Const_Xml_Iterator
begin(const TiXmlElement* p)
{ return Const_Xml_Iterator(p->FirstChildElement()); }

inline Const_Xml_Iterator
end(const TiXmlElement*)
{ return Const_Xml_Iterator(nullptr); }

#endif /* LIBRPG_XML_H */
