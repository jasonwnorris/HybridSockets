// UdpSocket.hpp

#ifndef __HS_UDPSOCKET_HPP__
#define __HS_UDPSOCKET_HPP__

// HS Includes
#include <HS/Address.hpp>

namespace HS
{
  class UdpSocket
  {
    public:
      UdpSocket();
      ~UdpSocket();

      bool Open(Uint16 p_Port = 0, int p_PacketSize = 1024);
      void Close();

      bool Send(const Address& p_Address, const std::string& p_Data);
      bool Receive(Address& p_Address, std::string& p_Data);

    private:
      UDPsocket m_Socket;
      UDPpacket* m_Packet;
  };
}

#endif
