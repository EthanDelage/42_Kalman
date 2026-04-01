#include <iostream>
#include <ostream>

#include "Application.hpp"

int main(int argc, char **argv) {
  double noise_scale = 1.;
  if (argc == 2) {
    try {
      noise_scale = std::stod(argv[1]);
      std::cout << "noise scale: " << noise_scale << std::endl;
    } catch (std::exception &e) {
      std::cerr << "noise_scale conversion error: " << e.what() << std::endl;
      return 1;
    }
  }
  try {
    Application app(noise_scale);
    app.run();
    return EXIT_SUCCESS;
  } catch (std::runtime_error &e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }
}
