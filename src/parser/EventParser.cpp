#include "parser/EventParser.hpp"

#include <Eigen/Dense>
#include <chrono>

static void router(std::istringstream &ss, event_t &event);
static void parse_acceleration(std::istringstream &ss, event_t &event);
static void parse_direction(std::istringstream &ss, event_t &event);
static void parse_position(std::istringstream &ss, event_t &event);
static void parse_true_position(std::istringstream &ss, event_t &event);
static void parse_speed(std::istringstream &ss, event_t &event);
static void parse_vector3d(std::istringstream &ss, Eigen::Vector3d &vec);
static std::chrono::milliseconds parse_timestamp(std::istringstream &str);
static int expect_char(std::istringstream &ss, char expected);

event_t EventParser::parse(std::istringstream &ss) {
  event_t event{};

  event.timestamp = parse_timestamp(ss);

  router(ss, event);
  return event;
}

static void router(std::istringstream &ss, event_t &event) {
  using parse_fn = void (*)(std::istringstream &, event_t &);
  using entry = std::pair<std::string, parse_fn>;
  std::string event_identifier;

  std::getline(ss, event_identifier);
  std::array<entry, 5> router_table = {{{"ACCELERATION", parse_acceleration},
                                        {"DIRECTION", parse_direction},
                                        {"POSITION", parse_position},
                                        {"TRUE POSITION", parse_true_position},
                                        {"SPEED", parse_speed}}};
  for (const auto &it : router_table) {
    if (it.first == event_identifier) {
      it.second(ss, event);
      if (ss.fail()) {
        throw std::runtime_error("router : parse error");
      }
      return;
    }
  }
  throw std::runtime_error("router : unknown event identifier (" +
                           event_identifier + ")");
}

static void parse_acceleration(std::istringstream &ss, event_t &event) {
  event.type = DataType::Acceleration;
  parse_vector3d(ss, event.vec);
}

static void parse_direction(std::istringstream &ss, event_t &event) {
  event.type = DataType::Direction;
  parse_vector3d(ss, event.vec);
}

static void parse_position(std::istringstream &ss, event_t &event) {
  event.type = DataType::Position;
  parse_vector3d(ss, event.vec);
}

static void parse_true_position(std::istringstream &ss, event_t &event) {
  event.type = DataType::TruePosition;
  parse_vector3d(ss, event.vec);
}

static void parse_speed(std::istringstream &ss, event_t &event) {
  event.type = DataType::Speed;
  ss >> event.scalar;
}
static void parse_vector3d(std::istringstream &ss, Eigen::Vector3d &vec) {
  ss >> vec[0];
  ss >> vec[1];
  ss >> vec[2];
}

static std::chrono::milliseconds parse_timestamp(std::istringstream &str) {
  size_t hours, minutes, seconds, milliseconds;

  if (expect_char(str, '[') == -1) {
    throw std::runtime_error("parse_timestamp : unexpected char");
  }
  str >> hours;
  if (expect_char(str, ':') == -1) {
    throw std::runtime_error("parse_timestamp : unexpected char");
  }
  str >> minutes;
  if (expect_char(str, ':') == -1) {
    throw std::runtime_error("parse_timestamp : unexpected char");
  }
  str >> seconds;
  if (expect_char(str, '.') == -1) {
    throw std::runtime_error("parse_timestamp : unexpected char");
  }
  str >> milliseconds;
  if (expect_char(str, ']') == -1) {
    throw std::runtime_error("parse_timestamp : unexpected char");
  }
  if (str.fail()) {
    throw std::runtime_error("parse_timestamp : parse error");
  }
  return std::chrono::milliseconds{
      (hours * 3600 + minutes * 60 + seconds) * 1000 + milliseconds};
}

static int expect_char(std::istringstream &ss, char expected) {
  int c = ss.get();
  if (c == std::char_traits<char>::eof() || static_cast<char>(c) != expected) {
    return -1;
  }
  return 0;
}