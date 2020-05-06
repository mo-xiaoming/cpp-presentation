#include <iostream>

int main() {
  for (int i{0}; i < 200; i++) {
    std::cout << i << ' ' << i * 20'000'000 << std::endl;
  }
  return 0;
}
