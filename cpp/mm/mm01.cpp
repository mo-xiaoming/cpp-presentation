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

  auto a0 = new int[4 * 1024];
  std::cout << "#### after 4k malloc\n";
  ::malloc_stats();
  std::cin.get();

  auto a1 = new int[64 * 1024];
  std::cout << "#### after 64k malloc\n";
  ::malloc_stats();
  std::cin.get();

  delete[] a1;
  std::cout << "#### free mapped 64k\n";
  ::malloc_stats();
  std::cin.get();

  delete[] a0;
  std::cout << "#### free first brked 4k\n";
  ::malloc_stats();
}
