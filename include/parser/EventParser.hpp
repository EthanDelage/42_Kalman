#ifndef KALMAN_EVENTPARSER_HPP
#define KALMAN_EVENTPARSER_HPP

#include <Eigen/Dense>
#include <chrono>

typedef struct event_s event_t;

class EventParser {
public:
  EventParser() = delete;

  static event_t parse(std::istringstream &str);
};

enum class DataType {
  Acceleration,
  Direction,
  Position,
  TruePosition,
  Speed,
};

struct event_s {
  DataType type;
  std::chrono::milliseconds timestamp;
  union {
    Eigen::Vector3d vec;
    double scalar;
  };
};

#endif // KALMAN_EVENTPARSER_HPP