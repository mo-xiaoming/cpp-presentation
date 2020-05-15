#include <algorithm>
#include <cstring>
#include <iostream>

int main() {
  for (int i = 0; i < 1024 * 1024; ++i) {
    auto p = new int[1024 * 1024];
#if 0
    std::fill_n(p, 1024 * 1024, 3);
#endif
    std::cerr << i * sizeof(int) << "MB allocated\n";
  }
}
