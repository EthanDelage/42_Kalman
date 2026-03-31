#ifndef KALMAN_MOTION_MODEL_HPP
#define KALMAN_MOTION_MODEL_HPP

#include "KalmanFilter.hpp"
#include "parser/EventParser.hpp"

#include <Eigen/Core>

Eigen::Matrix3d rotation_matrix(const Eigen::Vector3d &euler_rotation);
Eigen::Vector3d transform_acceleration(const Eigen::Vector3d &acceleration,
                                       const Eigen::Matrix3d &rotation);
Eigen::Vector3d compute_velocity(const Eigen::Vector3d &velocity,
                                 const Eigen::Vector3d &acceleration,
                                 double dt);
Eigen::Vector3d compute_position(std::vector<event_t> events,
                                 KalmanFilter &filter);

#endif // KALMAN_MOTION_MODEL_HPP
