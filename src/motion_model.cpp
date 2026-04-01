#include "motion_model.hpp"

#include "data/print.hpp"
#include <iostream>

Eigen::Matrix3d rotation_matrix(const Eigen::Vector3d &euler_rotation) {
  double roll = euler_rotation[0], pitch = euler_rotation[1],
         yaw = euler_rotation[2];
  Eigen::Matrix3d r_x, r_y, r_z;

  r_x << 1, 0, 0, 0, cos(roll), -sin(roll), 0, sin(roll), cos(roll);

  r_y << cos(pitch), 0, sin(pitch), 0, 1, 0, -sin(pitch), 0, cos(pitch);

  r_z << cos(yaw), -sin(yaw), 0, sin(yaw), cos(yaw), 0, 0, 0, 1;

  return r_z * r_y * r_x;
}

Eigen::Vector3d compute_position(std::vector<event_t> events,
                                 KalmanFilter &filter) {
  Eigen::Vector3d acceleration, gps;
  Eigen::Vector<double, 6> state;
  bool acceleration_init = false, gps_init = false;

  for (event_t event : events) {
    switch (event.type) {
    case DataType::Acceleration:
      acceleration_init = true;
      acceleration = event.vec;
      break;
    case DataType::Position:
      gps_init = true;
      gps = event.vec;
      break;
    case DataType::TruePosition:
      state.head<3>() = event.vec;
      state.tail<3>() = filter.get_state().tail<3>();
      filter.set_state(state);
      return event.vec;
    default:
      break;
    }
  }
  if (acceleration_init) {
    filter.predict(acceleration);
  } else {
    throw std::runtime_error("Acceleration not initialized");
  }
  if (gps_init) {
    filter.update(gps);
  }
  return filter.get_state().segment<3>(0);
}
