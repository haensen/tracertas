#!/bin/sh
lcov -d ./build/CMakeFiles/tracertas_test.dir/ -c -o coverage.info
lcov --extract coverage.info '*/src/*' -o coverage.info
genhtml -o ./coverageReport -p . coverage.info
rm coverage.info
