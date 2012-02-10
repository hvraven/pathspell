#ifndef LIBRPG_ACCESS_H
#define LIBRPG_ACCESS_H

#include "element.h"
#include <memory>
#include <unordered_map>
#include <vector>

namespace RPG
{

	template <typename U>
	class Access_Iterator;
	template <typename U>
	class Const_Access_Iterator;

	template <typename T = Element>
	class Access
	{
		typedef std::unordered_map<Identifier, std::shared_ptr<T>> Element_Map;
	public:
		Access<T>() {};

		virtual bool has_element(const Identifier&) const;
		virtual const T& get_element(const Identifier&) const;
		virtual void import_elements(const Access<T>&);
		virtual std::vector<T> export_elements() const;

		virtual void add_element(const T&);

		virtual T& operator[](const Identifier& identifier)
			{ return *(elements_[identifier]); }

		typedef Access_Iterator<T> iterator;
		typedef Const_Access_Iterator<T> const_iterator;
		//typedef ptrdiff_t difference_type;
		typedef size_t size_type;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;

		iterator begin() { return iterator(*this, 0); }
		iterator end() { return iterator(*this, elements_.length()); }
		
	private:
		Element_Map elements_;

		template <typename U> friend class Access_Iterator;
		template <typename U> friend class Const_Access_Iterator;
	};

	template <typename U = Element>
	class Access_Iterator
	{
	public:
		Access_Iterator(Access<U>& access, int position)
			: access_(access), position_(position) {}

		bool operator==(const Access_Iterator<U>& it) const;
		bool operator!=(const Access_Iterator<U>& it) const
			{ return !(*this == it); }
		U& operator*();
		Access_Iterator<U>& operator++() { position_++; return *this; }
		Access_Iterator<U> operator++(int);
		Access_Iterator<U>& operator--() { position_--; return *this; }
		Access_Iterator<U> operator--(int);


	private:
		Access<U>& access_;
		int position_;
	};

	/**** Access ******************************************************/

	template <typename T>
	bool Access<T>::has_element(const Identifier& identifier) const
	{
		return (elements_.find(identifier) != elements_.end());
	}

	template <typename T>
	const T& Access<T>::get_element(const Identifier& identifier) const
	{
		return **(elements_.find(identifier));
	}

	template <typename T>
	void Access<T>::import_elements(const Access<T>& import)
	{
		for (typename Access<T>::const_iterator it = import.begin();
				it != import.end(); it++)
			elements_[it->first].reset(it->second);
	}

	template <typename T>
	std::vector<T> Access<T>::export_elements() const
	{
		std::vector<T> result;
		for (typename Access<T>::const_iterator it = this->begin();
				it != this->end(); it++)
			result.push_back(*it);
		return result;
	}

	template <typename T>
	void Access<T>::add_element(const T& element)
	{
		(*this)[element.get_identifier()].reset(element);
	}

	/**** Access_Iterator *********************************************/

	template <typename U>
	bool Access_Iterator<U>::operator==(const Access_Iterator<U>& it) const
	{
		if (access_ == it.access_)
		{
			if (position_ < access_.elements_.length())
			{
				if (it.position_ < access_.elements_.length())
					return (position_ == it.position_);
				else
					return false;
			}
			else
			{
				if (it.position_ < access_.elements_.length())
					return false;
				else /* both at end */
					return true;
			}
		}
		else
			return false;
	}

	template <typename U>
	U& Access_Iterator<U>::operator*()
	{
		if (position_ < access_.elements_.length())
			return *(access_.begin() + position_);
		else
			return 0;
	}

	template <typename U>
	Access_Iterator<U> Access_Iterator<U>::operator++(int)
	{
		Access_Iterator<U> clone(*this);
		++position_;
		return clone;
	}

	template <typename U>
	Access_Iterator<U> Access_Iterator<U>::operator--(int)
	{
		Access_Iterator<U> clone(*this);
		--position_;
		return clone;
	}
}

#endif /* LIBRPG_ACCESS_H */
