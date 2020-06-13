#include <cstdio>
#include <cstring>
#include <string>
#include <string_view>

inline constexpr auto toU(char c) noexcept -> char {
  return 'a' <= c && c <= 'z' ? static_cast<char>(c - 32) : c;
}

constexpr auto compareASCII(std::string_view a, std::string_view b) noexcept
    -> bool {
  if (a.size() != b.size())
    return false;

  for (auto i = 0U; i < a.size(); ++i)
    if (toU(a[i]) != toU(b[i]))
      return false;

  return true;
}

constexpr auto compareASCII(char const *a, char const *b) noexcept -> bool {
  while (*a != '\0' && *b != '\0') {
    if (toU(*a++) != toU(*b++)) {
      return false;
    }
  }

  return *a == *b;
}

using namespace std::string_literals;
using namespace std::literals;

int main() {
  return compareASCII("hello", "world") + compareASCII("hello", "HELLO"s) +
         compareASCII("hello", "world"sv) + compareASCII("hello"s, "HELLO"s) +
         compareASCII("hello"s, "world"sv) + compareASCII("hello"sv, "HELLO"sv);
}
