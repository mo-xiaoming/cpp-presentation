#include <cstring>
#include <iostream>

int main() {
  for (int i = 0; i < 4 * 1024; ++i) {
    auto p = new int[1024 * 1024];
    for (int j = 0; j < 1024 * 1024; ++j) {
      p[j] = j;
    }
    std::cerr << i * sizeof(int) << "MB allocated\n";
  }
}
