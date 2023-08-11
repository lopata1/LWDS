cmake_minimum_required(VERSION "3.10")

project("lwds")

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

file(GLOB_RECURSE HEADER_FILES "include/lwds/*.h")
file(GLOB_RECURSE SOURCE_FILES "src/*.cc")

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})

include_directories(${CMAKE_SOURCE_DIR}/include)

enable_testing()

add_library(lwds_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})

add_subdirectory(tests)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/config.ini
     DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)