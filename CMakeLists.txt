cmake_minimum_required(VERSION 3.0.0)
project(SoftRenderer VERSION 0.1.0)

# file(GLOB SOURCES "ThirdParty/*.h" "src/math/*.cpp" "src/graphics/*.cpp" "src/platform/*.cpp" "src/*.cpp")

set(SOURCES 
    src/math/mathUtils.cpp
    src/graphics/texture.cpp
    src/graphics/shader.cpp
    src/graphics/mesh.cpp
    src/graphics/renderer.cpp
    src/platform/viewport.cpp
    src/main.cpp
)

configure_file(configuration/root_directory.h.in configuration/root_directory.h)
include_directories(${CMAKE_BINARY_DIR}/configuration)

add_executable(SoftRenderer ${SOURCES})

target_compile_features(${PROJECT_NAME} PUBLIC c_std_11)

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/src)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/ThirdParty)