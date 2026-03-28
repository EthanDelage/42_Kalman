#ifndef KALMAN_SPEED_HPP
#define KALMAN_SPEED_HPP

#include <ctime>

typedef struct speed_s {
  double scalar;
  std::time_t timestamp;
} speed_t;

#endif // KALMAN_SPEED_HPP