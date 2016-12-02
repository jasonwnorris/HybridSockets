// main.cpp

// HS Includes
#include <HS/UdpSocket.hpp>
// STL Includes
#include <iostream>

void RunAsServer()
{
  HS::UdpSocket socket;
  socket.Open(5000);

  HS::Address address;
  std::string data;

  while (true)
  {
    if (socket.Receive(address, data))
    {
      std::cout << "Received[" << address.Host << ":" << address.Port << "]: \"" << data << "\"" << std::endl;

      if (data == "quit")
      {
        break;
      }
    }
  }

  socket.Close();
}

void RunAsClient()
{
  HS::Address address = HS::Address::Parse("localhost", 5000);
  HS::UdpSocket socket;
  socket.Open();
  socket.Send(address, "hello");
  socket.Send(address, "foobar");
  socket.Send(address, "quit");
  socket.Close();
}

int main(int p_ArgCount, char** p_ArgVars)
{
  if (p_ArgCount > 1)
  {
    RunAsServer();
  }
  else
  {
    RunAsClient();
  }

  return 0;
}
