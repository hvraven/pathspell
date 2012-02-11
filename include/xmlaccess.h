#ifndef LIBRPG_XMLACCESS_H
#define LIBRPG_XMLACCESS_H

#define TIXML_USE_STL

#include "access.h"
#include "spell.h"
#include <tinyxml.h>

namespace RPG
{
	typedef std::string filetype;

	class Xml_Access
	{
	public:
		Xml_Access(const filetype& file);
		virtual ~Xml_Access();

	private:
		const filetype file_path_;
		TiXmlDocument doc_;
	};

	namespace Pathfinder
	{

		class Spell_Xml_Access : public Xml_Access, public Access<Spell>
		{
		};

	} /* namespace Pathfinder */
} /* namespace RPG */

#endif /* LIBRPG_XMLACCESS_H */
