#ifndef LIBRPG_ACCESS_H
#define LIBRPG_ACCESS_H

#include "element.h"
#include <unordered_map>
#include <vector>

namespace RPG
{

	template <typename T>
	class Access
	{
		typedef std::unordered_map<Identifier, T> Element_Map;
	public:
		Access<T>() {};

		virtual bool has_element(const Identifier&) const;
		virtual const T& get_element(const Identifier&) const;
		virtual void import_elements(const Access<T>&);
		virtual std::vector<T> export_elements() const;

		virtual void add_element(const T&);

		virtual T& operator[](const Identifier& identifier)
			{ return elements_[identifier]; }

		typedef typename Element_Map::iterator iterator;
		typedef typename Element_Map::const_iterator const_iterator;
		iterator begin() { return elements_.begin(); }
		iterator end() { return elements_.end(); }
		
	private:
		Element_Map elements_;
	};


	/**** Access ********************************************/

	template <typename T>
	bool Access<T>::has_element(const Identifier& identifier) const
	{
		return (elements_.find(identifier) != elements_.end());
	}

	template <typename T>
	const T& Access<T>::get_element(const Identifier& identifier) const
	{
		return *(elements_.find(identifier));
	}

	template <typename T>
	void Access<T>::import_elements(const Access<T>& import)
	{
		for (Access<T>::const_iterator it = import.begin();
				it != import.end(); it++)
			elements_[it->first] = it->second;
	}

	template <typename T>
	std::vector<T> Access<T>::export_elements() const
	{
		std::vector<T> result;
		for (Access<T>::const_iterator it = this->begin();
				it != this->end(); it++)
			result.push_back(this->end());
		return result;
	}

	template <typename T>
	void Access<T>::add_element(const T& element)
	{
		(*this)[element.get_identifier()] = element;
	}

}

#endif /* LIBRPG_ACCESS_H */
