cmake_minimum_required(VERSION 3.16)

enable_testing()

include(GoogleTest)

file(GLOB_RECURSE TEST_SOURCE_FILES "${PROJECT_SOURCE_DIR}/test/*/*_test.cpp")



message(STATUS "=======================Gradle Test Module==========================")
message(STATUS "${TEST_SOURCE_FILES}")

foreach (TEST_SOURCE_FILE ${TEST_SOURCE_FILES})
    get_filename_component(TEST_FILE_SOURCE_NAME ${TEST_SOURCE_FILE} NAME)

    string(REPLACE ".cpp" "" TEST_FILE_NAME ${TEST_FILE_SOURCE_NAME})
    message(STATUS "TEST Unit: ${TEST_FILE_NAME}")

    add_executable(${TEST_FILE_NAME} EXCLUDE_FROM_ALL ${TEST_SOURCE_FILE})
    target_link_libraries(${TEST_FILE_NAME} 10G gtest gmock_main nlohmann_json::nlohmann_json)
    set_target_properties(${TEST_FILE_NAME}
            PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/test"
            COMMAND ${TEST_FILE_NAME}
            )
    add_test(NAME ${TEST_FILE_NAME} COMMAND ${TEST_FILE_NAME})
endforeach ()