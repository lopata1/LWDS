cmake_minimum_required(VERSION "3.10")

project("WebServer")

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

file(GLOB_RECURSE HEADER_FILES "include/*.h")
file(GLOB_RECURSE SOURCE_FILES "src/*.cc")

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}/include/databases
	${CMAKE_CURRENT_SOURCE_DIR}/include/html
	${CMAKE_CURRENT_SOURCE_DIR}/include/pages
)

enable_testing()

add_library(web_server_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})

add_subdirectory(tests)