#ifndef LIBRPG_PATHFINDER_SPELLTOKEN_H
#define LIBRPG_PATHFINDER_SPELLTOKEN_H

namespace RPG
{
	namespace Pathfinder
	{

		enum Saving_Throw_Token
		{
			Will,
			Fortitude,
			Reflex
		};

		enum Saving_Throw_Value_Token
		{
			Nil,
			Half,
			Negates,
			No,
			Partial,
			Disbelief
		};

	} /* namespace Pathfinder */
} /* namespace RPG */

#endif /* LIBRPG_PATHFINDER_SPELLTOKEN_H */
