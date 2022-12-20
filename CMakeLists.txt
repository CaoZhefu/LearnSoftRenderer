cmake_minimum_required(VERSION 3.0.0)
project(SoftRenderer VERSION 0.1.0)

find_package(SDL2 CONFIG REQUIRED)

file(GLOB SOURCES "*.h" "*.cpp" "ThirdParty/*.h")

configure_file(configuration/root_directory.h.in configuration/root_directory.h)
include_directories(${CMAKE_BINARY_DIR}/configuration)

add_executable(SoftRenderer ${SOURCES})
target_link_libraries(SoftRenderer PRIVATE SDL2::SDL2 SDL2::SDL2main)