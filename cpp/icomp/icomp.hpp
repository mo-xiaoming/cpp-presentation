#pragma once

#include <string_view>

constexpr int icmp2(std::string_view a, std::string_view b) noexcept {
	if (a.size() != b.size()) {
		return a.size() > b.size() ? 1 : -1;
	}
	for (auto i=0U; i<a.size(); ++i) {
		if (a[i] != b[i]) {
			return a[i] > b[i] ? 1 : -1;
		}
	}
	return 0;
}
