find_package(spdlog REQUIRED)

function(add_new_target name)
    add_executable(${name} ${name}.cpp)
    target_link_libraries(${name} PRIVATE spdlog::spdlog)
endfunction()

add_new_target(rvo)
add_new_target(errno)
add_new_target(bool_int)
add_new_target(exception)
add_new_target(optional)