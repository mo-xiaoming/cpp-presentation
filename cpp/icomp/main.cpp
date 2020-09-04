#include <benchmark/benchmark.h>
#include <string>
#include <string_view>
#include <algorithm>

#include "icomp.hpp"

namespace {
	void ipw_to_upper(std::string& s) {
		std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) -> unsigned char { return std::toupper(c); });
	}

	int ipw_icmp(std::string a, std::string b) {
		ipw_to_upper(a);
		ipw_to_upper(b);
		return a.compare(b);
	}

	auto const A = std::string("hello");
	auto const B = std::string("world");
	auto const C = std::string("hell");
	auto const D = std::string("hellx");
}

static void SameLengthIpw(benchmark::State& state) {
	for (auto _ : state) {
		benchmark::DoNotOptimize(ipw_icmp(A, B));
	}
}
BENCHMARK(SameLengthIpw);

static void SameLengthMine2(benchmark::State& state) {
	for (auto _ : state) {
		benchmark::DoNotOptimize(icmp2(A, B));
	}
}
BENCHMARK(SameLengthMine2);

static void DiffLengthIpw(benchmark::State& state) {
	for (auto _ : state) {
		benchmark::DoNotOptimize(ipw_icmp(B, C));
	}
}
BENCHMARK(DiffLengthIpw);

static void DiffLengthMine2(benchmark::State& state) {
	for (auto _ : state) {
		benchmark::DoNotOptimize(icmp2(B, C));
	}
}
BENCHMARK(DiffLengthMine2);

static void LastLetterIpw(benchmark::State& state) {
	for (auto _ : state) {
		benchmark::DoNotOptimize(ipw_icmp(A, D));
	}
}
BENCHMARK(LastLetterIpw);

static void LastLetterMine2(benchmark::State& state) {
	for (auto _ : state) {
		benchmark::DoNotOptimize(icmp2(A, D));
	}
}
BENCHMARK(LastLetterMine2);
