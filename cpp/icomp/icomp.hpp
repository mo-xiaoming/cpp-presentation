#pragma once

#include <cctype>
#include <string_view>

constexpr auto icmp2(std::string_view a, std::string_view b) noexcept -> int {
    constexpr auto to_upper = [](unsigned char c) { return std::toupper(c); };

    if (a.size() != b.size()) {
        return a.size() > b.size() ? 1 : -1;
    }
    for (auto i = 0U; i < a.size(); ++i) {
        auto const x = to_upper(a[i]);
        auto const y = to_upper(b[i]);
        if (x != y) {
            return x > y ? 1 : -1;
        }
    }
    return 0;
}
