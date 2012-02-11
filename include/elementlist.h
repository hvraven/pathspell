#ifndef LIBRPG_ELEMENTLIST_H
#define LIBRPG_ELEMENTLIST_H

#include "element.h"
#include "access.h"

namespace RPG
{
	template <typename T>
	class Element_List_Iterator;
	template <typename T>
	class Const_Element_List_Iterator;

	template <typename T = Element>
	class Element_List
	{
	public:
		Element_List<T>(Access<T>& access)
			: access_(access) {}
		virtual ~Element_List<T>() {}

		typedef Element_List_Iterator<T> iterator;
		typedef Const_Element_List_Iterator<T> const_iterator;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;

		virtual bool has_element(const Identifier& identifier)
			{ return access_.has_element(identifier); }

		virtual reference operator[](const Identifier& identifier)
			{ return *(access_[identifier]); }

		iterator begin() { return iterator(*this, 0); }
		iterator begin() const { return const_iterator(*this, 0); }
		iterator end() { return iterator(*this, access_.number_of_elements()); }
		iterator end() const
			{ return const_iterator(*this, access_.number_of_elements()); }

	protected:
		Access<T>& access_;
	};

	template <typename T = Element>
	class Element_List_Iterator
	{
	public:
		Element_List_Iterator(Element_List<T>& list, int position)
			: list_(list), position_(position) {}

		bool operator==(const Element_List_Iterator<T>& it) const;
		bool operator!=(const Element_List_Iterator<T>& it) const
			{ return !(*this == it); }
		T& operator*() { return *(list_.elements_.begin() + position_); }
		T* operator->() { return (list_.elements_.begin() + position_); }
		Element_List_Iterator<T>& operator++() { position_++; return *this; }
		Element_List_Iterator<T> operator++(int);
		Element_List_Iterator<T>& operator--() { position_--; return *this; }
		Element_List_Iterator<T> operator--(int);

	private:
		Element_List<T>& list_;
		int position_;
	};

	template <typename T = Element>
	class Const_Element_List_Iterator
	{
	public:
		Const_Element_List_Iterator(const Element_List<T>& list, int position)
			: list_(list), position_(position) {}

		bool operator==(const Const_Element_List_Iterator<T>& it) const;
		bool operator!=(const Const_Element_List_Iterator<T>& it) const
			{ return !(*this == it); }
		const T& operator*() const
			{ return *(list_.elements_.begin() + position_); }
		const T* operator->() const
			{ return (list_.elements_.begin() + position_); }
		Const_Element_List_Iterator<T>& operator++() { position_++; return *this; }
		Const_Element_List_Iterator<T> operator++(int);
		Const_Element_List_Iterator<T>& operator--() { position_--; return *this; }
		Const_Element_List_Iterator<T> operator--(int);

	private:
		const Element_List<T>& list_;
		int position_;
	};

	/**** Element_List ************************************************/

	/**** Element_List_Iterator ***************************************/

	template <typename T>
	bool Element_List_Iterator<T>::operator==
		(const Element_List_Iterator<T>& it) const
	{
		if (list_ == it.list_)
		{
			if (position_ < list_.elements_.length())
			{
				if (it.position_ < list_.elements_.length())
					return (position_ == it.position_);
				else
					return false;
			}
			else
			{
				if (it.position_ < list_.elements_.length())
					return false;
				else /* both at end */
					return true;
			}
		}
		else
			return false;
	}

	template <typename T>
	Element_List_Iterator<T> Element_List_Iterator<T>::operator++(int)
	{
		Element_List_Iterator<T> temp = clone *this;
		position_++;
		return temp;
	}

	template <typename T>
	Element_List_Iterator<T> Element_List_Iterator<T>::operator--(int)
	{
		Element_List_Iterator<T> temp = clone *this;
		position_--;
		return temp;
	}

	/**** Const_Element_List_Iterator *********************************/

	template <typename T>
	bool Const_Element_List_Iterator<T>::operator==
		(const Const_Element_List_Iterator<T>& it) const
	{
		if (list_ == it.list_)
		{
			if (position_ < list_.elements_.length())
			{
				if (it.position_ < list_.elements_.length())
					return (position_ == it.position_);
				else
					return false;
			}
			else
			{
				if (it.position_ < list_.elements_.length())
					return false;
				else /* both at end */
					return true;
			}
		}
		else
			return false;
	}

	template <typename T>
	Const_Element_List_Iterator<T> Const_Element_List_Iterator<T>::operator++(int)
	{
		Const_Element_List_Iterator<T> temp = clone *this;
		position_++;
		return temp;
	}

	template <typename T>
	Const_Element_List_Iterator<T> Const_Element_List_Iterator<T>::operator--(int)
	{
		Const_Element_List_Iterator<T> temp = clone *this;
		position_--;
		return temp;
	}

}
#endif /* LIBRPG_ELEMENTLIST_H */
