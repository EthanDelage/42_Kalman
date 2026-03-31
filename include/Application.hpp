#ifndef KALMAN_APPLICATION_HPP
#define KALMAN_APPLICATION_HPP
#include "KalmanFilter.hpp"
#include "UdpSocket.hpp"
#include "parser/MessageParser.hpp"

class Application {
public:
  Application();

  void run();

private:
  UdpSocket _udp_socket;
  MessageParser _parser;
  KalmanFilter _filter;
  bool _exit;

  void send_ready_msg() const;
  void send_position(const Eigen::Vector3d &pos) const;
  std::vector<event_t> read_message();
  Eigen::Vector3d compute_initial_state(std::vector<event_t> &events);
  static KalmanFilter init_kalman_filter(double dt);
};

#endif // KALMAN_APPLICATION_HPP