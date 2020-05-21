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

  std::cout << "#### allocate another int\n";
  auto b = new int[1024];
  ::malloc_stats();
  std::cin.get();

  std::cout << "#### free bottom 1024 * 1024 ints\n";
  std::for_each(begin(a), end(a), [](auto p) { delete[] p; });
  ::malloc_stats();
  std::cin.get();

  std::cout << "#### free top int\n";
  delete[] b;
  ::malloc_stats();
  std::cin.get();

  std::cout << "#### after trimming\n";
  ::malloc_trim(0);
  ::malloc_stats();
}
