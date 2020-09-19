#include "logger.hpp"

#include <atomic>
#include <cstdio>
#include <memory>

namespace {
struct Default_output_stream : logging::Output_stream {
    void output(std::string_view msg) override { std::puts(msg.data()); }
};

struct DefaultLogger {
    void set_out_stream(std::shared_ptr<logging::Output_stream> out) {
        out_ = std::move(out);
    }

    void set_level(logging::Level level) { level_ = level; }

    void info(std::string_view msg) {
        if (level_ <= logging::Level::info) {
            out_->output(msg);
        }
    }

private:
    std::atomic<logging::Level> level_{logging::Level::info};
    std::shared_ptr<logging::Output_stream> out_{
        std::make_shared<Default_output_stream>()};
};

auto instance() -> DefaultLogger& {
    static DefaultLogger logger;
    return logger;
}
} // namespace

namespace logging {
Output_stream::~Output_stream() = default;

void Logger::set_out_stream(std::shared_ptr<Output_stream> out) {
    instance().set_out_stream(std::move(out));
}
void Logger::set_level(Level level) { instance().set_level(level); }

void Logger::info(std::string_view msg) { instance().info(msg); }
} // namespace logging
