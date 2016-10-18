// UdpSocket.cpp

// HS Includes
#include <HS/UdpSocket.hpp>
// STL Includes
#include <sstream>

namespace HS
{
  UdpSocket::UdpSocket()
  {
    if (SDL_Init(0) < 0)
    {
        SDL_Log("[HS::UdpSocket] Failed to initialize SDL2: %s", SDL_GetError());
    }
    else
    {
        SDL_Log("[HS::UdpSocket] Initialized SDL2.");
    }

    if (SDLNet_Init() < 0)
    {
        SDL_Log("[HS::UdpSocket] Failed to initialize SDL_net: %s", SDLNet_GetError());
    }
    else
    {
        SDL_Log("[HS::UdpSocket] Initialized SDL2_net.");
    }
  }

  UdpSocket::~UdpSocket()
  {
    SDLNet_Quit();
    SDL_Log("[HS::UdpSocket] Quit SDL2_net.");

    SDL_Quit();
    SDL_Log("[HS::UdpSocket] Quit SDL2.");
  }

  bool UdpSocket::Open(int p_Port, int p_PacketSize)
  {
    m_Socket = SDLNet_UDP_Open(p_Port);
    if (m_Socket == nullptr)
    {
        SDL_Log("[HS::UdpSocket] Failed to open socket: %s", SDLNet_GetError());
        return false;
    }

    SDL_Log("[HS::UdpSocket] Opened UDP socket on port %d.", p_Port);

    m_Packet = SDLNet_AllocPacket(p_PacketSize);
    if (m_Packet == nullptr)
    {
        SDL_Log("[HS::UdpSocket] Failed to allocate packet: %s", SDLNet_GetError());
        return false;
    }

    SDL_Log("[HS::UdpSocket] Allocated packet.");

    return true;
  }

  void UdpSocket::Close()
  {
    SDLNet_FreePacket(m_Packet);
    SDL_Log("[HS::UdpSocket] Freed packet.");

    SDLNet_UDP_Close(m_Socket);
    SDL_Log("[HS::UdpSocket] Closed socket.");
  }

  bool UdpSocket::Send(const std::string& p_Host, int p_Port, const std::string& p_Data)
  {
    if (SDLNet_ResolveHost(&m_Packet->address, p_Host.c_str(), p_Port) < 0)
    {
        SDL_Log("[HS::UdpSocket] Failed to resolve host: %s", SDLNet_GetError());
        return false;
    }

    int length = p_Data.length();
    std::memcpy(m_Packet->data, p_Data.c_str(), length);
    m_Packet->len = length;

    if (SDLNet_UDP_Send(m_Socket, -1, m_Packet) == 0)
    {
        SDL_Log("[HS::UdpSocket] Failed to send: %s", SDLNet_GetError());
        return false;
    }

    return true;
  }

  bool UdpSocket::Receive(std::string& p_Data, std::string& p_Address)
  {
    int code = SDLNet_UDP_Recv(m_Socket, m_Packet);
    if (code > 0)
    {
      Uint8* parts = (Uint8*)&m_Packet->address.host;
      std::ostringstream os;
      os << static_cast<unsigned short>(parts[0]) << "."
         << static_cast<unsigned short>(parts[1]) << "."
         << static_cast<unsigned short>(parts[2]) << "."
         << static_cast<unsigned short>(parts[3]) << ":"
         << m_Packet->address.port;

      p_Data = std::string(m_Packet->data, m_Packet->data + m_Packet->len);
      p_Address = os.str();

      return true;
    }
    else if (code < 0)
    {
        SDL_Log("[HS::UdpSocket] Failed to receive: %s", SDLNet_GetError());
    }

    return false;
  }
}
