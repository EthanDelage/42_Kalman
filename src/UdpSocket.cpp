#include "UdpSocket.hpp"

#include <arpa/inet.h>
#include <array>
#include <netinet/in.h>
#include <stdexcept>
#include <cstring>

#define KALMAN_UDP_PORT 4242
#define KALMAN_UDP_ADDR INADDR_ANY
#define BUFFER_SIZE 2048

UdpSocket::UdpSocket() {
  struct sockaddr_in addr;

  addr.sin_family = AF_INET;
  addr.sin_port = htons(KALMAN_UDP_PORT);
  addr.sin_addr.s_addr = htonl(KALMAN_UDP_ADDR);
  _socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
  if (_socket_fd == -1) {
    throw std::runtime_error(std::string("UdpSocket: socket: ") +
                             strerror(errno));
  }
  set_recv_timeout(1);
  if (connect(_socket_fd, reinterpret_cast<struct sockaddr *>(&addr),
              sizeof(addr)) == -1) {
    throw std::runtime_error(std::string("UdpSocket: connect: ") +
                             strerror(errno));
  }
}

std::string UdpSocket::recv() const {
  std::array<char, BUFFER_SIZE> buffer{};

  ssize_t len = ::recv(_socket_fd, buffer.data(), buffer.size(), 0);
  if (len == -1) {
    throw std::runtime_error(std::string("UdpSocket::recv : recv: ") +
                             strerror(errno));
  }
  return {buffer.data(), static_cast<std::string::size_type>(len)};
}

void UdpSocket::send(const std::string &str) const {
  ssize_t len = ::send(_socket_fd, str.data(), str.size(), 0);
  if (len == -1) {
    throw std::runtime_error(std::string("UdpSocket::send : send") +
                             strerror(errno));
  }
  if (static_cast<std::string::size_type>(len) != str.size()) {
    throw std::runtime_error(
        std::string("UdpSocket::send : message partially sent") +
        strerror(errno));
  }
}

void UdpSocket::set_recv_timeout(int second) const {
  struct timeval tv;
  tv.tv_sec = second;
  tv.tv_usec = 0;

  setsockopt(_socket_fd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
}