#pragma once

#include <cstdint>
#include <memory>
#include <string_view>

namespace logging {
struct Output_stream {
    Output_stream() = default;
    Output_stream(Output_stream const&) = delete;
    Output_stream(Output_stream&&) = delete;
    auto operator=(Output_stream const&) -> Output_stream& = delete;
    auto operator=(Output_stream&&) -> Output_stream& = delete;
    virtual ~Output_stream();
    virtual void output(std::string_view msg) = 0;
};

enum class Level : uint8_t { debug, info, error, off };

struct Logger {
    static void set_out_stream(std::shared_ptr<Output_stream> out);

    static void set_level(Level level);

    static void info(std::string_view msg);
};

} // namespace logging
