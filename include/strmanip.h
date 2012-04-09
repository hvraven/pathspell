#ifndef LIBRPG_STRMANIP_H
#define LIBRPG_STRMANIP_H

#include <string>

namespace RPG
{

  std::string to_lower( const std::string& );
  void str_lower( std::string& );

  std::string to_upper( const std::string& );
  void str_upper( std::string& );

} /* namespace RPG */

#endif // LIBRPG_STRMANIP_H
