// TcpSocket.hpp

#ifndef __HS_TCPSOCKET_HPP__
#define __HS_TCPSOCKET_HPP__

// SDL2 Includes
#include <SDL2/SDL_net.h>
// STL Includes
#include <string>

namespace HS
{
  class TcpSocket
  {
    public:
      TcpSocket(int p_Port);
      ~TcpSocket();

      bool Send(const std::string& p_Data);
      bool Receive(std::string& p_Data);

    private:
      TCPsocket m_Socket;
  };
}

#endif
