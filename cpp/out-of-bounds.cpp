// g++ -std=c++17 -g -Og
#include <vector>

void foo(std::vector<int> &v) {
	v[3] = 0;
}

int main() {
	std::vector a{1, 3, 4};
	foo(a);
}
