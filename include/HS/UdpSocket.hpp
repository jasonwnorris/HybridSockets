// UdpSocket.hpp

#ifndef __HS_UDPSOCKET_HPP__
#define __HS_UDPSOCKET_HPP__

// SDL2 Includes
#include <SDL2/SDL_net.h>
// STL Includes
#include <string>

namespace HS
{
  class UdpSocket
  {
    public:
      UdpSocket();
      ~UdpSocket();

      bool Open(int p_Port = 0, int p_PacketSize = 1024);
      void Close();

      bool Send(const std::string& p_Host, int p_Port, const std::string& p_Data);
      bool Receive(std::string& p_Data, std::string& p_Address);

    private:
      UDPsocket m_Socket;
      UDPpacket* m_Packet;
  };
}

#endif
