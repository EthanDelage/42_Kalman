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

  void send_ready_msg() const;
  void send_position(const Eigen::Vector3d &pos) const;
  std::vector<event_t> read_message();
  static KalmanFilter init_kalman_filter();
};

#endif // KALMAN_APPLICATION_HPP