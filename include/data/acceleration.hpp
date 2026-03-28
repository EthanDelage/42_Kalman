#ifndef KALMAN_ACCELEROMETER_HPP
#define KALMAN_ACCELEROMETER_HPP

#include <Eigen/Dense>

typedef struct acceleration_s {
  Eigen::Vector3d vec;
  std::time_t timestamp;
} acceleration_t;

#endif // KALMAN_ACCELEROMETER_HPP
