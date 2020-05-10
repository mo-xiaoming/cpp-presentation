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
  std::array<int *, 1 << 10> a;
  std::generate(begin(a), end(a), [] { return new int[1 << 10]; });
  std::for_each(begin(a), end(a) - 1, [](auto &p) {
    delete[] p;
    p = nullptr;
  });
  std::this_thread::sleep_for(3s);
  delete[] a.back();
}

int main() {
  auto pid = static_cast<uint64_t>(getpid());
  std::cout << "#### (" << pid << ")\n";

  std::cout << "#### before malloc\n";
  ::malloc_stats();
  std::cin.get();

  std::array<std::thread, 4> a;
  std::generate(begin(a), end(a), [] { return std::thread(tf1); });

  std::cout << "#### thread destroyed\n";
  std::this_thread::sleep_for(1s);
  ::malloc_stats();

  std::for_each(begin(a), end(a), [](auto &t) { t.join(); });
}
