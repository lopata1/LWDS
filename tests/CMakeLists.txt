cmake_minimum_required(VERSION "3.10")

include(CTest)

file(GLOB_RECURSE TEST_FILES "*_test.cc")

add_executable(tests ${TEST_FILES})
target_link_libraries(tests gtest_main lwds_lib)

add_test(NAME HttpRequestTest COMMAND tests)