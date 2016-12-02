// Address.cpp

// HS Includes
#include <HS/Address.hpp>

namespace HS
{
  Address Address::Parse(const std::string& p_Hostname, Uint16 p_Port)
  {
    Address address;

    IPaddress ipAddress;
    if (SDLNet_ResolveHost(&ipAddress, p_Hostname.c_str(), p_Port) < 0)
    {
      SDL_Log("[HS::Address] Failed to resolve host: %s", SDLNet_GetError());
    }
    else
    {
      address.Host = ipAddress.host;
      address.Port = ipAddress.port;
    }

    return address;
  }
}
