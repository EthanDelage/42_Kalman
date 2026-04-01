#include "KalmanFilter.hpp"

#include <Eigen/Dense>

KalmanFilter::KalmanFilter(const Eigen::Vector<double, 6> &x,
                           const Eigen::Matrix<double, 6, 6> &F,
                           const Eigen::Matrix<double, 6, 3> &B,
                           const Eigen::Matrix<double, 3, 6> &H,
                           const Eigen::Matrix<double, 6, 6> &Q,
                           const Eigen::Matrix<double, 3, 3> &R,
                           const Eigen::Matrix<double, 6, 6> &P)
    : _x(x), _F(F), _B(B), _H(H), _Q(Q), _R(R), _P(P) {}

void KalmanFilter::predict(const Eigen::Vector<double, 3> &u) {
  _x = _F * _x + _B * u;              // A priori state estimate
  _P = _F * _P * _F.transpose() + _Q; // A priori estimate covariance
}

void KalmanFilter::update(const Eigen::Vector<double, 3> &z) {
  Eigen::Vector<double, 3> y;    // Innovation vector
  Eigen::Matrix<double, 3, 3> S; // Innovation Covariance
  Eigen::Matrix<double, 6, 3> K; // Kalman Gain
  Eigen::Matrix<double, 6, 6> I = Eigen::Matrix<double, 6, 6>::Identity();

  y = z - _H * _x;
  S = _H * _P * _H.transpose() + _R;
  K = _P * _H.transpose() * S.inverse();
  _x = _x + K * y;
  _P = (I - K * _H) * _P;
}

Eigen::Vector<double, 6> KalmanFilter::get_state() const { return _x; }

void KalmanFilter::set_state(const Eigen::Vector<double, 6> &x) { _x = x; }