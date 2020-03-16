#include <thread>

int main() {
    bool flag{false};
    std::thread s{[&flag]{ flag = true; }};

    while (!flag)
        ;

    s.join();
}
