#ifndef LIBRPG_ELEMENTSORTLIST_H
#define LIBRPG_ELEMENTSORTLIST_H

#include "elementlist.h"

namespace RPG
{

	template <typename T>
	class ElementSortList<T> : public RPG::ElementList<T>
	{

	};

}

#endif /* LIBRPG_ELEMENTSORTLIST_H */
