#include <optional>
#include <variant>

#include <spdlog/spdlog.hpp>

constexpr auto fail_value = 1;

static std::optional<int> foo2(int i) { return i != fail_value ? std::optional(3) : std::nullopt; }

enum class Error_code : std::uint8_t { error1, error2 };
template <>
struct [[maybe_unused]] fmt::formatter<Error_code>
    : formatter<std::string_view>{template <typename Format_context> auto format(Error_code code, Format_context& ctx){
          static constexpr std::array<std::string_view, 3> codes = {"error1", "error2"};
auto const s = codes[std::underlying_type_t<Error_code>(code)]; // NOLINT
return formatter<std::string_view>::format(s, ctx);
}
}
;

static std::variant<int, Error_code> foo3(int i) {
    if (i != fail_value) {
        return 3;
    }
    return Error_code::error1;
}

int main(int argc, char** /*argv*/) {
    if (auto const i = foo2(argc); !i) {
        spdlog::critical("some error");
    }
    if (auto const i = foo3(argc); std::get_if<Error_code>(&i)) {
        spdlog::critical("error from foo3: {}", std::get<Error_code>(i));
    }
}
