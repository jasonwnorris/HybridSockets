// TcpSocket.cpp

// HS Includes
#include <HS/TcpSocket.hpp>

namespace HS
{
  TcpSocket::TcpSocket(int p_Port)
  {
    if (SDL_Init(0) < 0)
    {
        SDL_Log("[HS::TcpSocket] Failed to initialize SDL2: %s", SDL_GetError());
    }
    else
    {
        SDL_Log("[HS::TcpSocket] Initialized SDL2.");
    }

    if (SDLNet_Init() < 0)
    {
        SDL_Log("[HS::TcpSocket] Failed to initialize SDL_net: %s", SDLNet_GetError());
    }
    else
    {
        SDL_Log("[HS::TcpSocket] Initialized SDL2_net.");
    }

    IPaddress address;
    if (SDLNet_ResolveHost(&address, nullptr, p_Port) < 0)
    {
        SDL_Log("[HS::TcpSocket] Failed resolve host address: %s", SDLNet_GetError());
    }
    else
    {
        SDL_Log("[HS::TcpSocket] Resolved host address.");
    }

    m_Socket = SDLNet_TCP_Open(&address);
    if (m_Socket == nullptr)
    {
        SDL_Log("[HS::TcpSocket] Failed to open socket: %s", SDLNet_GetError());
    }
    else
    {
        SDL_Log("[HS::TcpSocket] Opened TCP socket on port %d.", p_Port);
    }
  }

  TcpSocket::~TcpSocket()
  {
    SDLNet_TCP_Close(m_Socket);
    SDL_Log("[HS::TcpSocket] Closed socket.");

    SDLNet_Quit();
    SDL_Log("[HS::TcpSocket] Quit SDL2_net.");

    SDL_Quit();
    SDL_Log("[HS::TcpSocket] Quit SDL2.");
  }

  bool TcpSocket::Send(const std::string& p_Data)
  {
    if (SDLNet_TCP_Send(m_Socket, p_Data.c_str(), p_Data.length()) < p_Data.length())
    {
      SDL_Log("[HS::TcpSocket] Failed to send: %s", SDLNet_GetError());

      return false;
    }

    return true;
  }

  bool TcpSocket::Receive(std::string& p_Data)
  {
    const int length = 1024;
    char data[length];

    int results = SDLNet_TCP_Recv(m_Socket, data, length);
    if (results < 0)
    {
      SDL_Log("[HS::TcpSocket] Failed to receive: %s", SDLNet_GetError());

      return false;
    }

    p_Data.assign(data, results);

    return true;
  }
}
