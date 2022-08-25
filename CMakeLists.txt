cmake_minimum_required(VERSION 3.0.0)
project(SoftRenderer VERSION 0.1.0)

file(GLOB SOURCES *.h *.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})