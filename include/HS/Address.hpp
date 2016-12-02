// Address.hpp

#ifndef __HS_ADDRESS_HPP__
#define __HS_ADDRESS_HPP__

// SDL2 Includes
#include <SDL2/SDL_net.h>
// STL Includes
#include <string>

namespace HS
{
  struct Address
  {
    Uint32 Host;
    Uint16 Port;

    static Address Parse(const std::string& p_Hostname, Uint16 p_Port);
  };
}

#endif
