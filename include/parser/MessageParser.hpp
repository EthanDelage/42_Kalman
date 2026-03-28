#ifndef KALMAN_MESSAGEPARSER_HPP
#define KALMAN_MESSAGEPARSER_HPP
#include "EventParser.hpp"

#define MSG_START_STR "MSG_START"
#define MSG_END_STR "MSG_END"

class MessageParser {
public:
  enum class MessageType {
    Start,
    Event,
    End,
    Undefined,
  };

  MessageParser();

  MessageType parse(std::istream &str);

  std::vector<EventParser::event_t> get_events() const;
  void clear_events();

private:
  std::vector<EventParser::event_t> _events;
  bool _message_started;
};

#endif // KALMAN_MESSAGEPARSER_HPP