#ifndef KALMAN_GYROSCOPE_HPP
#define KALMAN_GYROSCOPE_HPP

#include <Eigen/Dense>

typedef struct direction_s {
  Eigen::Vector3d vec;
  std::time_t timestamp;
} direction_t;

#endif // KALMAN_GYROSCOPE_HPP