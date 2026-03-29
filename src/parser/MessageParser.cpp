#include "parser/MessageParser.hpp"

MessageParser::MessageParser() : _message_started(false) {}

MessageParser::MessageType MessageParser::parse(std::istream &str) {
  std::string first_word;
  const std::streampos pos = str.tellg();

  str >> first_word;

  str.clear();
  str.seekg(pos);

  if (first_word == MSG_START_STR) {
    _message_started = true;
    return MessageType::Start;
  }
  if (first_word == MSG_END_STR) {
    _message_started = false;
    return MessageType::End;
  }
  if (_message_started) {
    _events.push_back(EventParser::parse(str));
    return MessageType::Event;
  }
  return MessageType::Undefined;
}

std::vector<EventParser::event_t> MessageParser::get_events() const {
  return _events;
}

void MessageParser::clear_events() { _events.clear(); }
