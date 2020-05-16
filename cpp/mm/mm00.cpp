#include <iostream>

extern char etext, edata, end;

int el;
int el_init = 3;
static int il;
static int il_init = 3;

int main() {
  static int ll;
  static int ll_init = 3;

  std::cout << std::hex;
  std::cout << "\tmain()   " << (uint64_t)main << '\n';
  std::cout << "### end of .text " << (uint64_t)&etext << '\n';
  std::cout << '\n';

  std::cout << "\tel_init  " << (uint64_t)&el_init << '\n';
  std::cout << "\til_init  " << (uint64_t)&il_init << '\n';
  std::cout << "\tll_init  " << (uint64_t)&ll_init << '\n';
  std::cout << "### end of .data " << (uint64_t)&edata << '\n';
  std::cout << '\n';

  std::cout << "\tel       " << (uint64_t)&el << '\n';
  std::cout << "\til       " << (uint64_t)&il << '\n';
  std::cout << "\tll       " << (uint64_t)&ll << '\n';
  std::cout << "### end of .bss  " << (uint64_t)&end << '\n';
}
