#pragma once

#include <cctype>
#include <string_view>

constexpr auto icmp2(std::string_view a, std::string_view b) noexcept -> int {
    constexpr auto to_upper = [](unsigned char c) { return std::toupper(c); };

    if (a.size() != b.size()) {
        return a.size() > b.size() ? 1 : -1;
    }
    for (auto i = 0U; i < a.size(); ++i) {
        auto const m = a[i];
        auto const n = b[i];
        if (m == n) {
            continue;
        }
        auto const x = to_upper(m);
        auto const y = to_upper(n);
        if (x != y) {
            return x - y;
        }
    }
    return 0;
}
