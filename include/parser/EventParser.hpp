#ifndef KALMAN_EVENTPARSER_HPP
#define KALMAN_EVENTPARSER_HPP

#include "data/acceleration.hpp"
#include "data/direction.hpp"
#include "data/position.hpp"
#include "data/speed.hpp"

class EventParser {
public:
  EventParser() = delete;

  enum class DataType {
    Acceleration,
    Direction,
    Position,
    Speed,
  };

  typedef struct {
    DataType type;
    union data_u {
      acceleration_t acceleration;
      direction_t direction;
      position_t position;
      speed_t speed;
    };
  } event_t;

  static event_t parse(std::istream &str);
};

#endif // KALMAN_EVENTPARSER_HPP