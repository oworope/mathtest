#include "mathtest.hpp"
#include <iostream>
#include <stdexcept>

int main() {
  const int count = 5;
  const int min = 1;
  const int max = 20;

  try {
    MathTest test(count, min, max);
    test.run();
    test.show_statistics();
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }

  return 0;
}