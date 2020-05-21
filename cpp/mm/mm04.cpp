#include <algorithm>
#include <array>
#include <iostream>
#include <memory>
#include <thread>

#include <sys/types.h>
#include <unistd.h>

#include <malloc.h>

using namespace std::chrono_literals;

void tf1() {
  std::array<int *, 1024 * 128> a;
  std::generate(begin(a), end(a), [] { return new int[1024]; });
  auto b = new int[1024];
  std::for_each(begin(a), end(a), [](auto p) { delete[] p; });
}

int main() {
  auto pid = static_cast<uint64_t>(getpid());
  std::cout << "#### (" << pid << ")\n";

  std::cout << "#### before malloc\n";
  ::malloc_stats();
  std::cin.get();

  std::array<std::thread, 4> a;
  std::generate(begin(a), end(a), [] { return std::thread(tf1); });
  std::for_each(begin(a), end(a), [](auto &t) { t.join(); });

  std::cout << "#### all threads finished\n";
  ::malloc_stats();

  std::cout << "wait for exit\n";
  std::cin.get();
}
