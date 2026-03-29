#include "data/print.hpp"

std::ostream &operator<<(std::ostream &os, const acceleration_t &acc) {
  os << '[' << acc.timestamp << "] - Acceleration: " << acc.vec[0] << ", "
     << acc.vec[1] << ", " << acc.vec[2];
  return os;
}

std::ostream &operator<<(std::ostream &os, const direction_t &dir) {
  os << '[' << dir.timestamp << "] - Direction: " << dir.vec[0] << ", "
     << dir.vec[1] << ", " << dir.vec[2];
  return os;
}

std::ostream &operator<<(std::ostream &os, const imu_t &imu) {
  os << imu.acceleration << std::endl << imu.direction;
  return os;
}

std::ostream &operator<<(std::ostream &os, const position_t &pos) {
  os << '[' << pos.timestamp << "] - Position: " << pos.vec[0] << ", "
     << pos.vec[1] << ", " << pos.vec[2];
  return os;
}

std::ostream &operator<<(std::ostream &os, const speed_t &speed) {
  os << '[' << speed.timestamp << "] - Speed: " << speed.scalar;
  return os;
}
