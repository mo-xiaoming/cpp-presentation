cmake_minimum_required(VERSION 3.16)

option(USE_VCPKG "Use vcpkg as package manager, default is conan" FALSE)
if(USE_VCPKG)
	set(CMAKE_TOOLCHAIN_FILE "/home/mx/projects/vcpkg/scripts/buildsystems/vcpkg.cmake")
endif()

project(IComp VERSION 1.0.0.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

		#####################
		#    flags
		#####################
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wshadow -march=native -mtune=native")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")


if(USE_VCPKG)
	find_package(benchmark REQUIRED)
	find_package(GTest REQUIRED)

			#####################
			#    main
			#####################
	add_executable(benchmark_icomp benchmark_icomp.cpp)
	target_include_directories(benchmark_icomp PRIVATE ${benchmark_INCLUDE_DIRS})
	target_link_libraries(benchmark_icomp PRIVATE benchmark::benchmark benchmark::benchmark_main)


			#####################
			#    tests
			#####################
	enable_testing()
	include(GoogleTest)
	add_executable(test_icomp test_icomp.cpp)
	target_include_directories(test_icomp PRIVATE ${GTEST_INCLUDE_DIRS})
	target_link_libraries(test_icomp PRIVATE GTest::GTest)
	gtest_discover_tests(test_icomp)
else()
	if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
		message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
		file(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/v0.15/conan.cmake"
			"${CMAKE_BINARY_DIR}/conan.cmake"
			TLS_VERIFY ON)
	endif()
	include(${CMAKE_BINARY_DIR}/conan.cmake)

	conan_cmake_run(
	REQUIRES
	boost/1.74.0
	gtest/1.10.0
	benchmark/1.5.1
	BASIC_SETUP
	CMAKE_TARGETS
	OPTIONS
	gtest:build_gmock=False
	benchmark:enable_lto=True
	BUILD
	missing)

			#####################
			#    main
			#####################
	add_executable(benchmark_icomp benchmark_icomp.cpp)
	target_link_libraries(benchmark_icomp PRIVATE CONAN_PKG::benchmark)


			#####################
			#    tests
			#####################
	enable_testing()
	include(GoogleTest)
	add_executable(test_icomp test_icomp.cpp)
	target_link_libraries(test_icomp PRIVATE CONAN_PKG::gtest)
	gtest_discover_tests(test_icomp)
endif()

