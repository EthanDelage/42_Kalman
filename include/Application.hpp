#ifndef KALMAN_APPLICATION_HPP
#define KALMAN_APPLICATION_HPP
#include "UdpSocket.hpp"
#include "parser/MessageParser.hpp"

class Application {
public:
  Application();

  void run();

private:
  UdpSocket _udp_socket;
  MessageParser _parser;
  // TODO: add kalman_filter attribute

  void send_ready_msg() const;
  std::vector<EventParser::event_t> read_message();
};

#endif // KALMAN_APPLICATION_HPP