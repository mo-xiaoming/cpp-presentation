#include <catch2/catch.hpp>

#include "foo.hpp"
#include "logger.hpp"

struct MockLogger {
    static void info(std::string_view /*unused*/) {}
    static void set_level(logging::Level /*unused*/) {}
};

TEST_CASE("test foo") {
    auto const f = [](int n) { return foo<MockLogger>(n); };
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

    int called() const { return called_; }

    std::string const& msg() const { return msg_; }

private:
    int called_ = 0;
    std::string msg_;
};

SCENARIO("level set and get of logger") {
    GIVEN("a logger with default log level") {
        auto out = std::make_shared<Mock_output_stream>();
        logging::Logger::set_out_stream(out);

        WHEN("it's log level set to debug") {
            logging::Logger::set_level(logging::Level::debug);
            THEN("info msg should be displayed") {
                constexpr std::string_view msg = "hello";
                logging::Logger::info(msg);
                CHECK(out->called() == 1);
                CHECK(out->msg() == msg);
            }
        }
    }
}
