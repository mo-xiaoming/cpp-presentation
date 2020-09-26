find_package(spdlog REQUIRED)

function(add_new_target name)
    add_executable(${name} ${name}.cpp)
    target_link_libraries(${name} PRIVATE spdlog::spdlog)
endfunction()

add_new_target(000)
add_new_target(001)
add_new_target(002)
add_new_target(003)