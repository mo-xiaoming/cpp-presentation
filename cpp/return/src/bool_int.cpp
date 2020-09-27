#include <array>

#include <spdlog/spdlog.h>

constexpr auto fail_value = 1;

static bool foo1(int i) { return i != fail_value; }

enum class Return_code : std::uint8_t { ok, error1, error2 };
template <> struct [[maybe_unused]] fmt::formatter<Return_code> : formatter<std::string_view> {
    template <typename Format_context> auto format(Return_code code, Format_context& ctx) {
        static constexpr std::array<std::string_view, 3> codes = {"ok", "error1", "error2"};
        auto const s = codes[std::underlying_type_t<Return_code>(code)]; // NOLINT
        return formatter<std::string_view>::format(s, ctx);
    }
};

static Return_code foo2(int i) { return i != fail_value ? Return_code::ok : Return_code::error1; }

int main(int argc, char** /*argv*/) {
    if (!foo1(argc)) {
        spdlog::error("error from foo1: false");
    }
    if (auto const code = foo2(argc); code != Return_code::ok) {
        spdlog::error("error from foo2: {}", code);
    }
}
