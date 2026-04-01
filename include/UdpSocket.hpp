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

  void set_recv_timeout(int second) const;
};

#endif // KALMAN_UDPSOCKET_HPP