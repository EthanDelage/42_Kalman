#include "Application.hpp"

#include "data/print.hpp"
#include "motion_model.hpp"

#include <iostream>

#define MSG_READY_STR "READY\n"

Application::Application() : _filter(init_kalman_filter()) {}

void Application::run() {
  send_ready_msg();

  std::vector<event_t> events = read_message();
  Eigen::Vector3d estimate_pos = compute_initial_state(events);
  send_position(estimate_pos);

  while (true) {
    events = read_message();
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

KalmanFilter Application::init_kalman_filter() {
  Eigen::Vector<double, 6> x;
  Eigen::Matrix<double, 6, 6> F;
  Eigen::Matrix<double, 6, 3> B;
  Eigen::Matrix<double, 3, 6> H;
  Eigen::Matrix<double, 6, 6> Q;
  Eigen::Matrix<double, 3, 3> R;
  Eigen::Matrix<double, 6, 6> P;

  return KalmanFilter(x, F, B, H, Q, R, P);
}