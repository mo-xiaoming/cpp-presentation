#include <algorithm>
#include <array>
#include <string>
#include <string_view>

#include <benchmark/benchmark.h>

#include "icomp.hpp"

namespace {
void ipw_to_upper(std::string& s) {
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c) { return std::toupper(c); });
}

auto ipw_icmp(std::string a, std::string b) -> int {
    ipw_to_upper(a);
    ipw_to_upper(b);
    return a.compare(b);
}

std::array<std::string, 4> const strings1 = {"hello", "world", "hell", "hellx"};
std::array<std::string, 4> const strings2 = {"hellx", "hell", "world", "hello"};
} // namespace

static void Ipworks(benchmark::State& state) {
    for (auto _ : state) {
        for (auto const& i : strings1) {
            for (auto const& j : strings2) {
                benchmark::DoNotOptimize(ipw_icmp(i, j));
            }
        }
    }
}
BENCHMARK(Ipworks);

static void Mine(benchmark::State& state) {
    for (auto _ : state) {
        for (auto const& i : strings1) {
            for (auto const& j : strings2) {
                benchmark::DoNotOptimize(icmp2(i, j));
            }
        }
    }
}
BENCHMARK(Mine);
