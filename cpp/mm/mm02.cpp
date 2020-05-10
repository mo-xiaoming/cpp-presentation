#include <algorithm>
#include <array>
#include <iostream>

#include <sys/types.h>
#include <unistd.h>

#include <malloc.h>

int main() {
  auto pid = static_cast<uint64_t>(getpid());
  std::cout << "#### (" << pid << ")\n";

  std::cout << "#### before malloc\n";
  ::malloc_stats();
  std::cin.get();

  auto a = std::array<int *, 1 << 10>();
  std::cout << "#### after malloc 1024 * 1024 ints\n";
  std::generate(begin(a), end(a), [] { return new int[1 << 10]; });
  ::malloc_stats();
  std::cin.get();

  std::cout << "#### after free 1023 * 1024 ints\n";
  std::for_each(begin(a), end(a) - 1, [](auto p) { delete[] p; });
  ::malloc_stats();
}
