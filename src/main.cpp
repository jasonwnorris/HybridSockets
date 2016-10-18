// main.cpp

// HS Includes
#include <HS/UdpSocket.hpp>
// STL Includes
#include <iostream>

void RunAsServer()
{
  HS::UdpSocket socket;
  socket.Open(5000);

  std::string data;
  std::string address;

  bool running = true;
  while (running)
  {
    if (socket.Receive(data, address))
    {
      std::cout << "Received[" << address << "]: \"" << data << "\"" << std::endl;

      if (data == "quit")
      {
        running = false;
      }
    }
  }

  socket.Close();
}

void RunAsClient()
{
  HS::UdpSocket socket;
  socket.Open();
  socket.Send("localhost", 5000, "hello");
  socket.Send("localhost", 5000, "foobar");
  socket.Send("localhost", 5000, "quit");
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
