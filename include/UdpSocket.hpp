#ifndef KALMAN_UDPSOCKET_HPP
#define KALMAN_UDPSOCKET_HPP
#include <string>

class UdpSocket {
public:
  UdpSocket();
  std::string recv() const;
  void send(const std::string &str) const;

private:
  int _socket_fd;
};

#endif // KALMAN_UDPSOCKET_HPP