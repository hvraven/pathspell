#ifndef LIBRPG_ELEMENT_H
#define LIBRPG_ELEMENT_H

#include <string>

typedef std::string Identifier

namespace RPG
{

	class Element
	{
	public:
		Element(const Identifier&);

		const Identifier& get_identifier() const 
		{
		  return identifier_;
		}

	private:
		const Identifier identifier_;
	};

}

#endif /* LIBRPG_ELEMENT_H */
