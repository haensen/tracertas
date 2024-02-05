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


# Force the script to use FetchContent and not CPM internally to fetch asio
option(ASIO_USE_CPM "Download Asio with CPM instead of FetchContent" OFF)
option(
  ASIO_CPM_FETCHCONTENT_COMPAT
  "Should asio be declared with FetchContent functions to be compatible. This doesn't not allow CPM cache to work."
  ON
)
# Download this repository
include(FetchContent)
FetchContent_Declare(
  asiocmake
  GIT_REPOSITORY "https://github.com/OlivierLDff/asio.cmake"
  GIT_TAG        "main"
)
FetchContent_MakeAvailable(asiocmake)

list(APPEND commonSrc
  src/as_number.cpp
  src/address.cpp
  src/tracert.cpp
  src/protocol_headers.cpp
  src/icmp_echo.cpp
  src/tracetree.cpp
  src/cli.cpp
  src/dns.cpp
  src/csv.cpp
)

list(APPEND tests
  test/address_test.cpp
  test/protocol_headers_test.cpp
  test/icmp_echo_test.cpp
  test/as_number_test.cpp
  test/cli_test.cpp
  test/tracetree_test.cpp
  test/dns_test.cpp
  test/csv_test.cpp
)

add_executable(
  tracertas_test
  ${commonSrc}
  ${tests}
)
target_link_libraries(
  tracertas_test
  GTest::gtest_main
  asio::asio
)
include(GoogleTest)
gtest_discover_tests(tracertas_test)

add_executable(
  tracertas
  ${commonSrc}
  src/main.cpp
)
target_link_libraries(
  tracertas
  asio::asio
)

file(COPY ipv4_asn.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug/)

include(FetchContent)
FetchContent_Declare(
  asn-info
  GIT_REPOSITORY "https://github.com/ipverse/asn-info"
  GIT_TAG        "master"
)
FetchContent_MakeAvailable(asn-info)

file(COPY ${CMAKE_CURRENT_BINARY_DIR}/_deps/asn-info-src/as.csv DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug/)
