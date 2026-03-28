#ifndef KALMAN_UDPSOCKET_HPP
#define KALMAN_UDPSOCKET_HPP
#include <array>

#define BUFFER_SIZE 2048

class UdpSocket {
public:
  std::string recv();                // TODO: throw exception
  void send(const std::string &str); // TODO: throw exception

private:
  int _socket_fd;
  std::array<char, BUFFER_SIZE> _buffer; // TODO: move to recv() method
};

#endif // KALMAN_UDPSOCKET_HPP