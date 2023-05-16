cmake_minimum_required(VERSION 3.16.6)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(mystl)

add_subdirectory(lib/doctest)

include_directories(${PROJECT_SOURCE_DIR}/src)

file(GLOB SOURCE_FILES "test/*.cpp")

add_executable(test ${SOURCE_FILES} src/initializer_list.h)

target_link_libraries(test PRIVATE doctest)

