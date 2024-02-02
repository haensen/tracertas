cmake_minimum_required(VERSION 3.14)
project(TracertAs)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

include(FetchContent)
FetchContent_Declare(
  cppicmplib
  GIT_REPOSITORY "https://github.com/markondej/cpp-icmplib"
  GIT_TAG        "master"
)
FetchContent_MakeAvailable(cppicmplib)
include_directories(${cppicmplib_SOURCE_DIR})
# message(DIR="${cppicmplib_SOURCE_DIR}")

add_executable(
  tracertas_test
  test/as_number_test.cpp
  test/address_test.cpp
  src/as_number.cpp
  src/address.cpp
  src/tracert.cpp
)
target_link_libraries(
  tracertas_test
  GTest::gtest_main
)

file(COPY ipv4_asn.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug/)

include(GoogleTest)
gtest_discover_tests(tracertas_test)

add_executable(
  tracertas
  src/as_number.cpp
  src/address.cpp
  src/tracert.cpp
  src/main.cpp
  src/cli.cpp
)