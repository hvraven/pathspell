#ifndef LIBRPG_ELEMENT_H
#define LIBRPG_ELEMENT_H

#include <string>


namespace RPG
{

	typedef std::string Identifier;

	class Element
	{
	public:
		Element();

		virtual const Identifier& get_identifier() const = 0;
	};

} /* namespace RPG */

#endif /* LIBRPG_ELEMENT_H */
