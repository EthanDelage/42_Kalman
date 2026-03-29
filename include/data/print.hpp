#ifndef KALMAN_PRINT_HPP
#define KALMAN_PRINT_HPP

#include "data/acceleration.hpp"
#include "data/direction.hpp"
#include "data/imu.hpp"
#include "data/position.hpp"
#include "data/speed.hpp"

std::ostream &operator<<(std::ostream &os, const acceleration_t &acc);
std::ostream &operator<<(std::ostream &os, const direction_t &dir);
std::ostream &operator<<(std::ostream &os, const imu_t &imu);
std::ostream &operator<<(std::ostream &os, const position_t &pos);
std::ostream &operator<<(std::ostream &os, const speed_t &speed);

#endif // KALMAN_PRINT_HPP