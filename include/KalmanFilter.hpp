#ifndef KALMAN_KALMANFILTER_HPP
#define KALMAN_KALMANFILTER_HPP
#include <Eigen/Core>

class KalmanFilter {
public:
  KalmanFilter(const Eigen::Vector<double, 6> &x,
               const Eigen::Matrix<double, 6, 6> &F,
               const Eigen::Matrix<double, 6, 3> &B,
               const Eigen::Matrix<double, 3, 6> &H,
               const Eigen::Matrix<double, 6, 6> &Q,
               const Eigen::Matrix<double, 3, 3> &R,
               const Eigen::Matrix<double, 6, 6> &P);

  void predict(const Eigen::Vector<double, 3> &u); // u -> Input vector
  void update(const Eigen::Vector<double, 3> &z);  // z -> Measurement vector

  Eigen::Vector<double, 6> get_state() const;
  void set_state(const Eigen::Vector<double, 6> &x);

private:
  Eigen::Vector<double, 6> _x;    // State vector
  Eigen::Matrix<double, 6, 6> _F; // State Transition model applied to x
  Eigen::Matrix<double, 6, 3> _B; // Control Input model applied to u
  Eigen::Matrix<double, 3, 6> _H; // Observation model (measurement)
  Eigen::Matrix<double, 6, 6> _Q; // Covariance of the process noise
  Eigen::Matrix<double, 3, 3> _R; // Covariance of the observation noise
  Eigen::Matrix<double, 6, 6> _P; // Estimate Covariance
};

#endif // KALMAN_KALMANFILTER_HPP
