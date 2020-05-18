#include <algorithm>
#include <cstring>
#include <iostream>
#include <new>

int main() {
  for (int i = 0; i < 1024 * 1024; ++i) {
    try {
      auto p = new int[1024 * 1024];
      std::fill_n(p, 1024 * 1024, 3);
    } catch (std::bad_alloc const &e) {
      std::cerr << e.what() << '\n';
      exit(1);
    }
    std::cerr << i * sizeof(int) << "MB allocated\n";
  }
}
