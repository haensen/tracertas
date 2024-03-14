cmake_minimum_required(VERSION 3.14)
project(TracertAs)

set(RELEASE_PATH "${CMAKE_CURRENT_BINARY_DIR}/tracertas")

set(GEN_COVERAGE OFF)
find_program(GCOV_FIND_RESULT gcov)
if(NOT ${GCOV_FIND_RESULT} STREQUAL GCOV_FIND_RESULT-NOTFOUND AND CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(GEN_COVERAGE ON)
endif()

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
  src/ip_info.cpp
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
  test/ip_info_test.cpp
  test/cli_test.cpp
  test/tracetree_test.cpp
  test/dns_test.cpp
  test/csv_test.cpp
  test/prefix_container_test.cpp
  test/tracert_test.cpp
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
gtest_discover_tests(tracertas_test WORKING_DIRECTORY ${RELEASE_PATH})
if (GEN_COVERAGE)
  target_compile_options(tracertas_test PRIVATE "--coverage")
  target_link_libraries(tracertas_test gcov)
endif()

add_executable(
  tracertas
  ${commonSrc}
  src/main.cpp
)
target_link_libraries(
  tracertas
  asio::asio
)

if (MINGW)
  target_link_libraries(tracertas ws2_32)
  target_link_libraries(tracertas mswsock)
  target_link_libraries(tracertas bcrypt)
  target_link_libraries(tracertas_test ws2_32)
  target_link_libraries(tracertas_test mswsock)
  target_link_libraries(tracertas_test bcrypt)
endif()

include(FetchContent)
FetchContent_Declare(
  asn-info
  GIT_REPOSITORY "https://github.com/ipverse/asn-info"
  GIT_TAG        "master"
)
FetchContent_MakeAvailable(asn-info)
include(FetchContent)
FetchContent_Declare(
  ix-networks
  GIT_REPOSITORY "https://github.com/haensen/ix-networks"
  GIT_TAG        "main"
)
FetchContent_MakeAvailable(ix-networks)

set_target_properties(tracertas PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${RELEASE_PATH})
set_target_properties(tracertas_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${RELEASE_PATH})
set_target_properties(tracertas PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${RELEASE_PATH})
set_target_properties(tracertas_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${RELEASE_PATH})
set_target_properties(tracertas PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${RELEASE_PATH})
set_target_properties(tracertas_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${RELEASE_PATH})

file(COPY ${CMAKE_CURRENT_BINARY_DIR}/_deps/asn-info-src DESTINATION ${RELEASE_PATH})

file(COPY ${CMAKE_CURRENT_BINARY_DIR}/_deps/ix-networks-src DESTINATION ${RELEASE_PATH})

if(NOT EXISTS ${RELEASE_PATH}/asPrefixes.txt)
  file(DOWNLOAD https://thyme.apnic.net/current/data-raw-table ${RELEASE_PATH}/asPrefixes.txt)
endif()
