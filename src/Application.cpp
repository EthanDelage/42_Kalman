#include "Application.hpp"

#include "data/print.hpp"
#include <iostream>

#define MSG_READY_STR "READY\n"

Application::Application() {}

void Application::run() {
  send_ready_msg();

  while (true) {
    std::vector<event_t> events = read_message();
    for (event_t event : events) {
      std::cout << event << std::endl;
      // TODO: process events
    }
    // TODO: send_response
  }
}

void Application::send_ready_msg() const { _udp_socket.send(MSG_READY_STR); }

std::vector<event_t> Application::read_message() {
  MessageParser::MessageType msg_type = MessageParser::MessageType::Undefined;

  _parser.clear_events();
  while (msg_type != MessageParser::MessageType::End) {
    std::string str = _udp_socket.recv();
    msg_type = _parser.parse(str);
  }
  return _parser.get_events();
}
