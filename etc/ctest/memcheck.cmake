set(ENV{CXXFLAGS} "-g")
set(CTEST_MEMORYCHECK_COMMAND "/usr/local/bin/valgrind")

ctest_memcheck()
