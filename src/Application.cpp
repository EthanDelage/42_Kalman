#include "Application.hpp"

#include "data/print.hpp"
#include "motion_model.hpp"

#include <iostream>

#define MSG_READY_STR "READY\n"
#define THETA_ACCEL 0.001
#define THETA_GYRO 0.01
#define THETA_GPS 0.1

Application::Application()
    : _filter(init_kalman_filter(1. / 100.)), _exit(false) {}

void Application::run() {
  send_ready_msg();

  std::vector<event_t> events = read_message();
  Eigen::Vector3d estimate_pos = compute_initial_state(events);
  send_position(estimate_pos);

  while (true) {
    events = read_message();
    if (_exit) {
      std::cout << "Exiting..." << std::endl;
      return;
    }
    estimate_pos = compute_position(events, _filter);
    send_position(estimate_pos);
  }
}

void Application::send_ready_msg() const { _udp_socket.send(MSG_READY_STR); }

void Application::send_position(const Eigen::Vector3d &pos) const {
  std::string pos_str = std::to_string(pos[0]) + ' ' + std::to_string(pos[1]) +
                        ' ' + std::to_string(pos[2]) + '\n';

  _udp_socket.send(pos_str);
}

std::vector<event_t> Application::read_message() {
  MessageParser::MessageType msg_type = MessageParser::MessageType::Undefined;

  _parser.clear_events();
  while (msg_type != MessageParser::MessageType::End) {
    std::string str = _udp_socket.recv();
    msg_type = _parser.parse(str);
    if (msg_type == MessageParser::MessageType::EndSimulation) {
      _exit = true;
      return std::vector<event_t>();
    }
  }
  return _parser.get_events();
}

Eigen::Vector3d
Application::compute_initial_state(std::vector<event_t> &events) {
  Eigen::Vector3d true_pos, direction, velocity;
  bool true_pos_init = false, direction_init = false, velocity_init = false;
  Eigen::Vector<double, 6> initial_state;

  for (event_t event : events) {
    std::cout << event << std::endl;
    switch (event.type) {
    case DataType::TruePosition:
      true_pos_init = true;
      true_pos = event.vec;
      break;
    case DataType::Direction:
      direction_init = true;
      direction = event.vec;
      break;
    case DataType::Speed:
      velocity_init = true;
      velocity << event.scalar / 3.6, 0, 0;
      break;
    default:
      break;
    }
  }

  if (!true_pos_init || !direction_init || !velocity_init) {
    throw std::runtime_error("Missing initial value");
  }
  velocity = rotation_matrix(direction) * velocity;
  initial_state << true_pos, velocity;
  _filter.set_state(initial_state);
  return true_pos;
}

KalmanFilter Application::init_kalman_filter(double dt) {
  Eigen::Vector<double, 6> x;
  Eigen::Matrix<double, 6, 6> F;
  Eigen::Matrix<double, 6, 3> B;
  Eigen::Matrix<double, 3, 6> H;
  Eigen::Matrix<double, 6, 6> Q;
  Eigen::Matrix<double, 3, 3> R;
  Eigen::Matrix<double, 6, 6> P;

  Eigen::Matrix3d identity3 = Eigen::Matrix3d::Identity();
  Eigen::Matrix3d zero3 = Eigen::Matrix3d::Zero();

  // State Transition model
  F.block<3, 3>(0, 0) = identity3;
  F.block<3, 3>(0, 3) = dt * identity3;
  F.block<3, 3>(3, 3) = identity3;
  F.block<3, 3>(3, 0) = zero3;

  // Control Input model
  B.block<3, 3>(0, 0) = std::pow(dt, 2) / 2 * identity3;
  B.block<3, 3>(3, 0) = dt * identity3;

  // Observation model
  H.block<3, 3>(0, 0) = identity3;
  H.block<3, 3>(0, 3) = zero3;

  // Process noise covariance
  Q.block<3, 3>(0, 0) = std::pow(dt, 4) / 4 * identity3;
  Q.block<3, 3>(0, 3) = std::pow(dt, 3) / 2 * identity3;
  Q.block<3, 3>(3, 0) = std::pow(dt, 3) / 2 * identity3;
  Q.block<3, 3>(3, 3) = std::pow(dt, 2) * identity3;
  Q *= THETA_ACCEL;

  // Observation noise covariance
  R = std::pow(THETA_GPS, 2) * identity3;

  // Estimate Covariance
  P = std::pow(THETA_ACCEL * THETA_GYRO, 2) *
      Eigen::Matrix<double, 6, 6>::Identity();

  return KalmanFilter(x, F, B, H, Q, R, P);
}