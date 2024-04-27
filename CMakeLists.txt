cmake_minimum_required(VERSION 3.16)
project(10G
        VERSION 2024.04.27
        DESCRIPTION "10G big File System"
        LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_INCLUDE_DIR "src/include")
#set(PROJECT_THIRD_PARTY_INCLUDE_DIR "third_party/include")
set(PROJECT_TEST_INCLUDE_DIR "test/include")



add_compile_options("-fexception")
add_link_options("-fexception")

