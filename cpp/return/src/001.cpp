// Exception Handling for C++: The exception handling mechanism
// 1. Makes it easier to adhere to the best practice
// 2. Gives error handling a more regular style
// 3. Makes error handling code more readable
// 4. Makes error handling code more amenable to tools
//
// Exceptions are used **primarily for error handling**
// NO CONTROL FLOW MANAGEMENT
//
// It is costly. If thrown, we have reached a point where cost
// is the least of our problems
//
// Progress
// 1. Allocate exception
// 2. Throw
// 3. Lookup
// 4. Cleanup
//   1. Stack unwind, look for catch
//   2. Catch
// 5. Resume exception (on catch frame):
//   1. If a 'finally' block exists, execute it
//   2. Execution resumes in the catch block
//
// Best practice
// 1. Derive your own exception from std::exception
// 2. Throw by value, catch by const ref, and re-throw using throw

#include <stdexcept>

#include <spdlog/spdlog.h>

struct My_exception : std::exception {
    explicit My_exception(std::string msg) : msg_(std::move(msg)) {}
    [[nodiscard]] char const* what() const noexcept override;

private:
    std::string msg_;
};

char const* My_exception::what() const noexcept { return msg_.c_str(); }

struct Resource_wrapper {
    Resource_wrapper() = default;
    Resource_wrapper(Resource_wrapper const&) = default;
    Resource_wrapper(Resource_wrapper&&) = default;
    Resource_wrapper& operator=(Resource_wrapper const&) = default;
    Resource_wrapper& operator=(Resource_wrapper&&) = default;
    ~Resource_wrapper() { spdlog::info("~Resource_wrapper"); }
};

static void throw_my_exception [[noreturn]] (std::string msg) { throw My_exception(std::move(msg)); }

static void foo(int i) {
    constexpr auto fail_value = 1;
    auto const rw = Resource_wrapper();
    if (i == fail_value) {
        throw_my_exception("Aloha from a exception");
    }
}

int main(int argc, char** /*argv*/) {
    try {
        foo(argc);
    } catch (std::exception const& e) { // MUST
        // it is implementation-defined whether any stack unwinding is done
        // if an exception is not caught
        spdlog::critical(e.what());
        return 1;
    } catch (...) {
        spdlog::critical("Unknown exception");
        return 1;
    }
}
