#ifndef KALMAN_MESSAGEPARSER_HPP
#define KALMAN_MESSAGEPARSER_HPP
#include "EventParser.hpp"

class MessageParser {
public:
  enum class MessageType {
    Start,
    Event,
    End,
    Undefined,
  };

  MessageType parse(std::istream &str);

  std::vector<EventParser::event_t> &get_events() const;
  void clear_events();

private:
  std::vector<EventParser::event_t> _events;
};

#endif // KALMAN_MESSAGEPARSER_HPP