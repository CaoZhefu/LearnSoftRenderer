cmake_minimum_required(VERSION 3.0.0)
project(SoftRenderer VERSION 0.1.0)

file(GLOB SOURCES "src/*.cpp" "src/platform/*.cpp")

configure_file(configuration/root_directory.h.in configuration/root_directory.h)
include_directories(${CMAKE_BINARY_DIR}/configuration)

add_executable(SoftRenderer ${SOURCES})

target_compile_features(${PROJECT_NAME} PUBLIC c_std_11)

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/src)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/ThirdParty)