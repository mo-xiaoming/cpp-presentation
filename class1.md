```cpp
#include <cstdio>

int initA() {
    std::puts("A");
    return 0;
};

int initB() {
    std::puts("B");
    return 0;
};

struct S {
    int a { initA() };
    int b { initB() };

    S() {}
    S(int a) : a(a) {}
};

int main() {
    auto s0 = S();
    auto s1 = S(3);
    auto s2 = s1;
}
```
