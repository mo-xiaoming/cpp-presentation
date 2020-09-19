#pragma once

#include <atomic>
#include <cstdint>
#include <string_view>
#include <type_traits>

namespace logging {
enum class Level : uint8_t { debug, info, error, off };

struct Default_output_stream {
    static void output(std::string_view msg) { std::puts(msg.data()); }
};

template <typename Output_stream = Default_output_stream>
requires std::is_default_constructible_v<Output_stream> struct Logger {
    static Output_stream& output_stream() { return impl.do_output_stream(); }

    static void set_level(Level level) { impl.do_set_level(level); }

    static void info(std::string_view msg) { impl.do_info(msg); }

    template <typename Func>
    requires std::is_invocable_v<Func> static void info(Func&& func) {
        info(std::forward<Func>(func)());
    }

private:
    static inline struct Impl {
        Output_stream& do_output_stream() { return out_; }

        void do_set_level(Level level) { level_ = level; }

        void do_info(std::string_view msg) {
            if (level_ <= Level::info) {
                out_.output(msg);
            }
        }

    private:
        std::atomic<Level> level_{Level::info};
        Output_stream out_;
    } impl;
};

} // namespace logging
