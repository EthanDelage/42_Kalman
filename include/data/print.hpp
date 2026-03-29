#ifndef KALMAN_PRINT_HPP
#define KALMAN_PRINT_HPP

#include "parser/EventParser.hpp"

std::ostream &operator<<(std::ostream &os, const event_t &event);

#endif // KALMAN_PRINT_HPP