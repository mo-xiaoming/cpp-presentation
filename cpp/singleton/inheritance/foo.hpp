#pragma once

#include "logger.hpp"

template <typename LoggerType = logging::Logger> auto foo(int n) -> int {
    constexpr auto dummy1 = 10;
    if (n > dummy1) {
        LoggerType::info([] { return "> 10"; });
        return 1;
    }
    constexpr auto dummy = 10;
    if (n < -dummy) {
        LoggerType::info("< -10");
        return -1;
    }
    LoggerType::set_level(logging::Level::info);
    return 0;
}
