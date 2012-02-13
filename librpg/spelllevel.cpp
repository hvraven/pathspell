#include "spellelements.h"
#include <sstream>

using namespace RPG::Pathfinder;

Spell_Level::Spell_Level()
: levels_()
{
}

Spell_Level::Spell_Level( const Spell_Level_Map& levels)
: levels_(levels)
{
}

Spell_Level::~Spell_Level()
{
}

std::string Spell_Level::print() const
{
	std::ostringstream temp;
	for (Spell_Level_Map::const_iterator it = levels_.begin() ;
			it != levels_.end() ; it++ )
		{
			temp << it->first
				<< " "
				<< it->second
				<< "; ";
		}
	std::string result = temp.str();
	if ( result != "" )
		result.erase( result.end() - 2, result.end() -1 );

	return result;
}

std::string Spell_Level::print( const std::string& level) const
{
	if ( levels_.find(level)->second )
	{
		std::ostringstream sresult;
		sresult << level
			<< " "
			<< levels_.find(level)->second;
		return sresult.str();
	}
	else
		return "";
}
