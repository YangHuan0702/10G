cmake_minimum_required(VERSION 3.16)
project(10G
        VERSION 2024.04.27
        DESCRIPTION "10G big File System"
        LANGUAGES C CXX)

SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)
SET(BUILD_SHARED_LIBS OFF)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_definitions("-DJSONFILE_PATH=/home/py/feedback_data.txt")

set(PROJECT_INCLUDE_DIR "src/include")
set(PROJECT_TEST_INCLUDE_DIR "test/include")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wno-unused-parameter -Wno-attributes")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -ggdb -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include_directories(${PROJECT_INCLUDE_DIR} ${PROJECT_TEST_INCLUDE_DIR})
include_directories(BEFORE src)

add_compile_options("-fexceptions")
add_link_options("-fexceptions")


add_subdirectory(src)
add_subdirectory(third_party)
add_subdirectory(test)

add_executable(main main.cpp)