#include "parser/MessageParser.hpp"

MessageParser::MessageParser() : _message_started(false) {}

MessageParser::MessageType MessageParser::parse(std::string &str) {
  std::istringstream ss(str);
  std::string first_word;
  const std::streampos pos = ss.tellg();

  ss >> first_word;

  ss.clear();
  ss.seekg(pos);

  if (first_word == MSG_START_STR) {
    _message_started = true;
    return MessageType::Start;
  }
  if (first_word == MSG_END_STR) {
    _message_started = false;
    return MessageType::End;
  }
  if (_message_started) {
    _events.push_back(EventParser::parse(ss));
    return MessageType::Event;
  }
  return MessageType::Undefined;
}

std::vector<event_t> MessageParser::get_events() const { return _events; }

void MessageParser::clear_events() { _events.clear(); }
