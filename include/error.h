#ifndef LIBRPG_ERROR_H
#define LIBRPG_ERROR_H

#include <exception>

namespace RPG
{
	namespace Error
	{

		struct Invalid_Argument : public std::exception
		{
			Invalid_Argument() {};
		};

	} /* namespace Error */
} /* namespace RPG */
#endif // LIBRPG_ERROR_H
