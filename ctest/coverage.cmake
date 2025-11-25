set(ENV{CXXFLAGS} "--coverage")
set(CTEST_COVERAGE_COMMAND "/usr/local/bin/gcov")

ctest_test()
ctest_coverage()
