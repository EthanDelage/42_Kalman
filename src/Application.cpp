#include "Application.hpp"

#include "data/print.hpp"
#include "motion_model.hpp"

#define MSG_READY_STR "READY\n"

Application::Application() {}

void Application::run() {
  KalmanFilter filter =
      KalmanFilter(Eigen::Vector<double, 6>(), Eigen::Matrix<double, 6, 6>(),
                   Eigen::Matrix<double, 6, 3>(), Eigen::Matrix<double, 3, 6>(),
                   Eigen::Matrix<double, 6, 6>(), Eigen::Matrix<double, 3, 3>(),
                   Eigen::Matrix<double, 6, 6>());

  send_ready_msg();

  while (true) {
    std::vector<event_t> events = read_message();
    Eigen::Vector3d estimate_pos = compute_position(events, filter);
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
