#ifndef KALMAN_EVENTPARSER_HPP
#define KALMAN_EVENTPARSER_HPP

#include <chrono>
#include <Eigen/Dense>

typedef struct event_s event_t;

class EventParser {
public:
  EventParser() = delete;

  enum class DataType {
    Acceleration,
    Direction,
    Position,
    TruePosition,
    Speed,
  };

  static event_t parse(std::istringstream &str);
};

typedef struct event_s {
  EventParser::DataType type;
  std::chrono::milliseconds timestamp;
  union {
    Eigen::Vector3d acceleration;
    Eigen::Vector3d direction;
    Eigen::Vector3d position;
    double speed;
  };
} event_t;

#endif // KALMAN_EVENTPARSER_HPP