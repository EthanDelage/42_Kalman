#ifndef KALMAN_POSITION_HPP
#define KALMAN_POSITION_HPP

#include <Eigen/Dense>
#include <ctime>

typedef struct position_s {
  Eigen::Vector3d vec;
  std::time_t timestamp;
} position_t;

#endif // KALMAN_POSITION_HPP