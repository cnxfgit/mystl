cmake_minimum_required(VERSION 3.19.2)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(mystl)

add_subdirectory(lib/doctest)

include_directories(${PROJECT_SOURCE_DIR}/src)

add_executable(test test/main_test.cpp test/vector_test.cpp)

target_link_libraries(test PRIVATE doctest)
