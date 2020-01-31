#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <initializer_list>
#include <array>
#include <complex>

struct S {
    S() = default;
    int i;
};

struct X {
    X();
    int i;
};

X::X() = default;

int main() {
    S s{};
    X x{};
    std::cout << s.i << std::endl;
    std::cout << x.i << std::endl;
}
