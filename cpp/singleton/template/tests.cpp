#include <catch2/catch.hpp>

#include "foo.hpp"
#include "logger.hpp"

struct Mock_logger {
    template <typename T> static void info(T&& /*unused*/) {}
    static void set_level(logging::Level /*unused*/) {}
};

TEST_CASE("test foo") {
    auto const f = [](int n) { return foo<Mock_logger>(n); };
    CHECK(f(11) == 1);   // NOLINT
    CHECK(f(-11) == -1); // NOLINT
    CHECK(f(0) == 0);    // NOLINT
}

struct Mock_output_stream {
    void output(std::string_view msg) {
        ++called_;
        msg_ = msg;
    }

    void reset() {
        called_ = 0;
        msg_.clear();
    }

    [[nodiscard]] int called() const { return called_; }

    [[nodiscard]] std::string const& msg() const { return msg_; }

private:
    int called_ = 0;
    std::string msg_;
};

using Mocked_logger = logging::Logger<Mock_output_stream>;

SCENARIO("logger set and get level") {
    constexpr std::string_view msg = "hello";
    GIVEN("a logger with default log level") {
        WHEN("set its log level to debug") {
            Mocked_logger::set_level(logging::Level::debug);
            THEN("should display info") {
                Mocked_logger::info(msg);
                CHECK(Mocked_logger::output_stream().called() == 1); // NOLINT
                CHECK(Mocked_logger::output_stream().msg() == msg);  // NOLINT
            }
        }

        Mocked_logger::output_stream().reset();
        WHEN("set its log level to info") {
            Mocked_logger ::set_level(logging::Level::info);
            THEN("should display info") {
                Mocked_logger::info(msg);
                CHECK(Mocked_logger::output_stream().called() == 1); // NOLINT
                CHECK(Mocked_logger::output_stream().msg() == msg);  // NOLINT
            }
        }

        Mocked_logger::output_stream().reset();
        WHEN("set its log level to error") {
            Mocked_logger ::set_level(logging::Level::error);
            THEN("should not display info") {
                Mocked_logger::info(msg);
                CHECK(Mocked_logger::output_stream().called() == 0); // NOLINT
                CHECK(Mocked_logger::output_stream().msg() == "");   // NOLINT
            }
        }

        Mocked_logger::output_stream().reset();
        WHEN("set its log level to off") {
            Mocked_logger::set_level(logging::Level::off);
            THEN("should not display info") {
                Mocked_logger::info(msg);
                CHECK(Mocked_logger::output_stream().called() == 0); // NOLINT
                CHECK(Mocked_logger::output_stream().msg() == "");   // NOLINT
            }
        }
    }
}
