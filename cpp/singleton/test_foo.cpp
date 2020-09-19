#include <catch2/catch.hpp>

#include "foo.hpp"
#include "logger.hpp"

struct Mock_logger {
    static void info(std::string_view /*unused*/) {}
    static void set_level(logging::Level /*unused*/) {}
};

TEST_CASE("test foo") {
    auto const f = [](int n) { return foo<Mock_logger>(n); };
    CHECK(f(11) == 1);   // NOLINT
    CHECK(f(-11) == -1); // NOLINT
    CHECK(f(0) == 0);    // NOLINT
}

struct Mock_output_stream : logging::Output_stream {
    void output(std::string_view msg) override {
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

SCENARIO("logger set and get level") {
    constexpr std::string_view msg = "hello";
    GIVEN("a logger with default log level") {
        auto out = std::make_shared<Mock_output_stream>();
        logging::Logger::set_out_stream(out);

        out->reset();
        WHEN("set its log level to debug") {
            logging::Logger::set_level(logging::Level::debug);
            THEN("should display info") {
                logging::Logger::info(msg);
                CHECK(out->called() == 1); // NOLINT
                CHECK(out->msg() == msg);  // NOLINT
            }
        }

        out->reset();
        WHEN("set its log level to info") {
            logging::Logger::set_level(logging::Level::info);
            THEN("should display info") {
                logging::Logger::info(msg);
                CHECK(out->called() == 1); // NOLINT
                CHECK(out->msg() == msg);  // NOLINT
            }
        }

        out->reset();
        WHEN("set its log level to error") {
            logging::Logger::set_level(logging::Level::error);
            THEN("should not display info") {
                logging::Logger::info(msg);
                CHECK(out->called() == 0); // NOLINT
                CHECK(out->msg() == "");   // NOLINT
            }
        }

        out->reset();
        WHEN("set its log level to off") {
            logging::Logger::set_level(logging::Level::off);
            THEN("should not display info") {
                logging::Logger::info(msg);
                CHECK(out->called() == 0); // NOLINT
                CHECK(out->msg() == "");   // NOLINT
            }
        }
    }
}
