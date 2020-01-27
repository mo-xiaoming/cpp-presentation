#include <array>
#include <vector>
#include <iostream>

void out_of_bound(std::vector<int> &v) {
	v[3] = 0;
}

void uninitialized_variable() {
	std::array<int, 3> a;
	std::cout << a[0] << '\n';
}

int main() {
	std::vector a{1, 3, 4};
	out_of_bound(a);

	uninitialized_variable();
}
