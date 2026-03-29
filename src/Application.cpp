#include "Application.hpp"

#include "data/print.hpp"
#include <iostream>

#define MSG_READY_STR "READY\n"

Application::Application() {}

void Application::run() {
  std::vector<EventParser::event_t> events;

  while (true) {
    events = read_message();
    for (EventParser::event_t event : events) {
      switch (event.type) {
      case EventParser::DataType::Acceleration:
        std::cout << event.data.acceleration << std::endl;
        break;
      case EventParser::DataType::Direction:
        std::cout << event.data.direction << std::endl;
        break;
      case EventParser::DataType::Position:
        std::cout << event.data.position << std::endl;
        break;
      case EventParser::DataType::Speed:
        std::cout << event.data.speed << std::endl;
        break;
        // TODO: handle TruePosition
      }
      // TODO: process events
    }
    // TODO: send_response
  }
}

void Application::send_ready_msg() const { _udp_socket.send(MSG_READY_STR); }

std::vector<EventParser::event_t> Application::read_message() {
  MessageParser::MessageType msg_type = MessageParser::MessageType::Undefined;

  _parser.clear_events();
  while (msg_type != MessageParser::MessageType::End) {
    std::istringstream msg_str(_udp_socket.recv());
    msg_type = _parser.parse(msg_str);
  }
  return _parser.get_events();
}
