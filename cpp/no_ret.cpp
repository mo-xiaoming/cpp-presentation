#include <cstdio>

int foo() {
    for (int i=0; i<10; ++i) {
        std::printf("%d\n", i);
    }
}

int main() {
    foo();
}
