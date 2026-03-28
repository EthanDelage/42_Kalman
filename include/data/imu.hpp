#ifndef KALMAN_IMU_HPP
#define KALMAN_IMU_HPP

#include "data/acceleration.hpp"
#include "data/direction.hpp"

typedef struct imu_s {
  acceleration_t acceleration;
  direction_t direction;
} imu_t;

#endif // KALMAN_IMU_HPP