#ifndef LIBRPG_ELEMENTLIST_H
#define LIBRPG_ELEMENTLIST_H

#include "element.h"
#include "access.h"

namespace RPG
{

	template<typename T>
	class ElementList<T>
	{
	public:
		virtual void add_element(const T&);
		virtual void remove_element(const T&);
		virtual bool has_element(const T&);
		virtual bool has_element(const Identifier&);

		virtual void import_elements(const Access&);
		virtual void export_elements(const Access&);
	};

}

#endif /* LIBRPG_ELEMENTLIST_H */
