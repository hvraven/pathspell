#ifndef LIBRPG_ACCESS_H
#define LIBRPG_ACCESS_H

#include "element.h"
#include <unordered_map>

namespace RPG
{

	template <typename T>
	class Access<T>
	{
	public:
		Access<T>() {};

		virtual bool has_element(const Identifier&) const;
		virtual const T& get_element(const Identifier&) const;
		virtual void import_elements(const Access<T>&);
		virtual std::vector<T> export_elements() const;

		virtual void add_element(const T&);
		
	private:
		std::unordered_map<Identifier, T> elements_;
	};

}

#endif /*  LIBRPG_ACCESS_H */
