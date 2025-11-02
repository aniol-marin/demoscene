set(CTEST_NIGHTLY_START_TIME "0:00:00 UTC")
#set(CTEST_SUBMIT_URL "https://...")

set(CTEST_SITE "molegames.net")
set(CTEST_BUILD_NAME "Trisquel")
set(CTEST_SOURCE_DIRECTORY "/home/bru/demoscene/")
set(CTEST_BINARY_DIRECTORY "${CTEST_SOURCE_DIRECTORY}/build")
set(CTEST_CMAKE_GENERATOR "Ninja")
find_program(CTEST_UPDATE_COMMAND "git")

set(ENV{CXXFLAGS} "-Wall -Wextra")
ctest_configure(OPTIONS "--compile-no-warning-as-error")
ctest_build(NUMBER_ERRORS errors NUMBER_WARNINGS warnings)
set(MAX_ERRORS 0)
set(MAX_WARNINGS 0)
if((errors GREATER MAX_ERRORS) OR (warnings GREATER MAX_WARNINGS))
	ctest_submit()
	message(FATAL_ERROR "build cancelled due to failing conditions:
		found ${errors}, ${MAX_ERRORS} permitted 
		found ${warnings}, ${MAX_WARNINGS} permitted "
	)
endif()

#[[ warnings as errors is ok for development, not for other build pipelines
ctest_configure(OPTIONS "--compile-no-warning-as-error")
]]#

# parallelization
#[[
cmake_host_system_information(RESULT nproc QUERY NUMBER_OF_LOGICAL_CORES)

ctest_build(PARALLEL_LEVEL ${nproc})

if(CTEST_MEMORYCHECK_COMMAND OR CTEST_MEMORYCHECK_TYPE)
	ctest_memcheck(PARALLEL_LEVEL ${nproc})
else()
	ctest_test(PARALLEL_LEVEL ${nproc})
endif()
]]#
