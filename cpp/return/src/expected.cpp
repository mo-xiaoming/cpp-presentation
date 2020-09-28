#include <tl/expected.hpp>

#include <spdlog/spdlog.h>

enum class Error_code : std::uint8_t { error1, error2 };
template <> struct [[maybe_unused]] fmt::formatter<Error_code> : formatter<std::string_view> {
    template <typename Format_context> auto format(Error_code code, Format_context& ctx) {
        static constexpr std::array<std::string_view, 3> codes = {"error1", "error2"};
        auto const s = codes[std::underlying_type_t<Error_code>(code)]; // NOLINT
        return formatter<std::string_view>::format(s, ctx);
    }
};

static tl::expected<int, Error_code> foo(int i) {
    if (i == 1) {
        return tl::make_unexpected(Error_code::error1);
    }
    return 3;
}

int main() {
    if (auto const r = foo(1); !r) {
        spdlog::critical("error: {}", r.error());
    }
    assert(*foo(2) == 3); // NOLINT
}
