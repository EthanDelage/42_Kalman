#include <iostream>
#include <ostream>

#include "Application.hpp"

int main(void) {
  try {
    Application app;
    app.run();
    return EXIT_SUCCESS;
  } catch (std::runtime_error &e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }
}
