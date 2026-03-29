#include "data/print.hpp"

std::ostream &operator<<(std::ostream &os, const event_t &event) {
  os << '[' << event.timestamp.count() << "] - ";
  switch (event.type) {
  case DataType::Acceleration:
    os << "Acceleration";
    break;
  case DataType::Direction:
    os << "Direction";
    break;
  case DataType::Position:
    os << "Position";
    break;
  case DataType::TruePosition:
    os << "TruePosition";
    break;
  case DataType::Speed:
    os << "Speed";
    break;
  }
  os << ": ";
  if (event.type == DataType::Speed) {
    os << event.scalar;
  } else {
    os << event.vec[0] << ", " << event.vec[1] << ", " << event.vec[2];
  }
  return os;
}
