cmake_minimum_required(VERSION 3.10)

project(fog VERSION 1.0)

add_executable(fog config.c fog.c)
find_package(Libssh2 REQUIRED CONFIG)
target_link_libraries(fog Libssh2::libssh2)
