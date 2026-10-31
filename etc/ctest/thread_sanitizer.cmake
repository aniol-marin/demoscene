set(ENV{CXXFLAGS} "-fsanitize=thread -fno-omit-frame-pointer")
set(CTEST_MEMORYCHECK_TYPE "ThreadSanitizer")

ctest_memcheck()
