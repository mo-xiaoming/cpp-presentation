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
  auto a = new int[100];
  std::this_thread::sleep_for(3s);
  delete[] a;
}

int main() {
  auto pid = static_cast<uint64_t>(getpid());
  std::cout << "#### (" << pid << ")\n";

  std::cout << "#### before malloc\n";
  ::malloc_stats();
  std::cin.get();

  {
    std::array<std::thread, 16> a;
    std::generate(begin(a), end(a), [] { return std::thread(tf1); });
    std::for_each(begin(a), end(a), [](auto &t) { t.join(); });
  }

  std::cout << "#### thread destroyed\n";
  ::malloc_stats();
}
