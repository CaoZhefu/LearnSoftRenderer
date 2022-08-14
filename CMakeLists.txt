cmake_minimum_required(VERSION 3.0.0)
project(SoftRenderer VERSION 0.1.0)

aux_source_directory(. SRC_LIST)

add_executable(SoftRenderer ${SRC_LIST})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})