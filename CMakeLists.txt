cmake_minimum_required(VERSION 3.16.6)

project(mystl)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(lib/doctest)

include_directories(${PROJECT_SOURCE_DIR}/src)

file(GLOB SOURCE_FILES "test/*.cpp")

add_executable(test ${SOURCE_FILES})

target_link_libraries(test PRIVATE doctest)

