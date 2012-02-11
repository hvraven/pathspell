#ifndef LIBRPG_ACCESS_H
#define LIBRPG_ACCESS_H

#include "element.h"
#include <memory>
#include <unordered_map>
#include <vector>

namespace RPG
{

	template <typename T>
	class Access_Iterator;
	template <typename T>
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
		iterator begin() const { return const_iterator(*this, 0); }
		iterator end() { return iterator(*this, elements_.length()); }
		iterator end() const { return const_iterator(*this, elements_.length()); }
		
	private:
		Element_Map elements_;

		friend class Access_Iterator<T>;
		friend class Const_Access_Iterator<T>;
	};

	template <typename T = Element>
	class Access_Iterator
	{
	public:
		Access_Iterator(Access<T>& access, int position)
			: access_(access), position_(position) {}

		bool operator==(const Access_Iterator<T>& it) const;
		bool operator!=(const Access_Iterator<T>& it) const
			{ return !(*this == it); }
		T& operator*();
		T* operator->();
		Access_Iterator<T>& operator++() { position_++; return *this; }
		Access_Iterator<T> operator++(int);
		Access_Iterator<T>& operator--() { position_--; return *this; }
		Access_Iterator<T> operator--(int);


	private:
		Access<T>& access_;
		int position_;
	};

	template <typename T = Element>
	class Const_Access_Iterator
	{
	public:
		Const_Access_Iterator(const Access<T>& access, int position)
			: access_(access), position_(position) {}

		bool operator==(const Const_Access_Iterator<T>& it) const;
		bool operator!=(const Const_Access_Iterator<T>& it) const
			{ return !(*this == it); }
		const T& operator*() const;
		const T* operator->() const;
		Const_Access_Iterator<T>& operator++() { position_++; return *this; }
		Const_Access_Iterator<T> operator++(int);
		Const_Access_Iterator<T>& operator--() { position_--; return *this; }
		Const_Access_Iterator<T> operator--(int);


	private:
		const Access<T>& access_;
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

	template <typename T>
	bool Access_Iterator<T>::operator==(const Access_Iterator<T>& it) const
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

	template <typename T>
	T& Access_Iterator<T>::operator*()
	{
		if (position_ < access_.elements_.length())
			return *(access_.begin() + position_);
		else
			return 0;
	}

	template <typename T>
	T* Access_Iterator<T>::operator->()
	{
		if (position_ < access_.elements_.length())
			return (access_.begin() + position_);
		else
			return 0;
	}

	template <typename T>
	Access_Iterator<T> Access_Iterator<T>::operator++(int)
	{
		Access_Iterator<T> clone(*this);
		++position_;
		return clone;
	}

	template <typename T>
	Access_Iterator<T> Access_Iterator<T>::operator--(int)
	{
		Access_Iterator<T> clone(*this);
		--position_;
		return clone;
	}

	/**** Const_Access_Iterator ***************************************/

	template <typename T>
	bool Const_Access_Iterator<T>::operator==
		(const Const_Access_Iterator<T>& it) const
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

	template <typename T>
	const T& Const_Access_Iterator<T>::operator*() const
	{
		if (position_ < access_.elements_.length())
			return *(access_.begin() + position_);
		else
			return 0;
	}

	template <typename T>
	const T* Const_Access_Iterator<T>::operator->() const
	{
		if (position_ < access_.elements_.length())
			return (access_.begin() + position_);
		else
			return 0;
	}

	template <typename T>
	Const_Access_Iterator<T> Const_Access_Iterator<T>::operator++(int)
	{
		Const_Access_Iterator<T> clone(*this);
		++position_;
		return clone;
	}

	template <typename T>
	Const_Access_Iterator<T> Const_Access_Iterator<T>::operator--(int)
	{
		Const_Access_Iterator<T> clone(*this);
		--position_;
		return clone;
	}
}

#endif /* LIBRPG_ACCESS_H */
