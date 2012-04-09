#include "xml.h"

inline Xml_Iterator
Xml_Iterator::operator++(int)
{
  Xml_Iterator temp = *this;
  p_->NextSiblingElement();
  return temp;
}

inline Xml_Iterator
Xml_Iterator::operator--(int)
{
  Xml_Iterator temp = *this;
  p_->PreviousSibling()->ToElement();
  return temp;
}

inline Const_Xml_Iterator
Const_Xml_Iterator::operator++(int)
{
  Const_Xml_Iterator temp = *this;
  p_->NextSiblingElement();
  return temp;
}

inline Const_Xml_Iterator
Const_Xml_Iterator::operator--(int)
{
  Const_Xml_Iterator temp = *this;
  p_->PreviousSibling()->ToElement();
  return temp;
}
