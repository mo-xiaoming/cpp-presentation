list(APPEND CMAKE_CTEST_ARGUMENTS "--output-on-failure")

find_package(Catch2 REQUIRED)
include(Catch)

add_executable(tests test_main.cpp tests.cpp ../src/rvo.cpp ../src/optional.cpp ../src/expected.cpp ../src/leaf.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2)
catch_discover_tests(tests)
