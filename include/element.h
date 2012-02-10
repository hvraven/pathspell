#ifndef LIBRPG_ELEMENT_H
#define LIBRPG_ELEMENT_H

#include <string>


namespace RPG
{

	typedef std::string Identifier;

	class Element
	{
	public:
		Element(const Identifier& identifier)
			: identifier_(identifier) {}

		const Identifier& get_identifier() const 
		{
		  return identifier_;
		}

	private:
		const Identifier identifier_;
	};

}

#endif /* LIBRPG_ELEMENT_H */
