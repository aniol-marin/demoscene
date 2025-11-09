
## This file should be placed in the root directory of your project.
## Then modify the CMakeLists.txt file in the root directory of your
## project to incorporate the testing dashboard.
##
## # The following are required to submit to the CDash dashboard:
##   ENABLE_TESTING()
##   INCLUDE(CTest)

set(CTEST_PROJECT_NAME mole_demo)
set(CTEST_NIGHTLY_START_TIME 01:00:00 UTC)

if(CMAKE_VERSION VERSION_GREATER 3.14)
  set(CTEST_SUBMIT_URL https://my.cdash.org/submit.php?project=mole_demo)
else()
  set(CTEST_DROP_METHOD "https")
  set(CTEST_DROP_SITE "my.cdash.org")
  set(CTEST_DROP_LOCATION "/submit.php?project=mole_demo")
endif()

###################################################
###################################################
###################################################

#[==[
set(CTEST_DROP_SITE_CDASH TRUE)
set(CTEST_NIGHTLY_START_TIME "0:00:00 UTC")
#set(CTEST_SUBMIT_URL "https://...")

set(CTEST_SITE "molegames.net")
set(CTEST_BUILD_NAME "Trisquel")
set(CTEST_SOURCE_DIRECTORY "/home/bru/demoscene/")
set(CTEST_BINARY_DIRECTORY "${CTEST_SOURCE_DIRECTORY}/build")
set(CTEST_CMAKE_GENERATOR "Ninja")
find_program(CTEST_UPDATE_COMMAND "git")

set(ENV{CXXFLAGS} "-Wall -Wextra")
#[[
ctest_configure(OPTIONS "--compile-no-warning-as-error")
ctest_build(NUMBER_ERRORS errors NUMBER_WARNINGS warnings)
]]#
set(MAX_ERRORS 0)
set(MAX_WARNINGS 0)
if((errors GREATER ${MAX_ERRORS}) OR (warnings GREATER ${MAX_WARNINGS}))
	ctest_submit()
	message(FATAL_ERROR "build cancelled due to failing conditions:
		found ${errors}, ${MAX_ERRORS} permitted 
		found ${warnings}, ${MAX_WARNINGS} permitted"
	)
endif()

#alternatively, make sure warning errors diminish over time
#[[
file(STRINGS "~/last_warning_count.txt" threshold LIMIT_COUNT 1)
if ((errors GREATER ${MAX_ERRORS}) OR (warnings GREATER threshold))
	ctest_submit()
	message(FATAL_ERROR "build cancelled due to increased number of warnings:
		found ${warnings}, ${threshold} permitted"
	)
endif()
file(WRITE "~/last_warning_count.txt" ${warnings})
]]#


#[[ warnings as errors is ok for development, not for other build pipelines
ctest_configure(OPTIONS "--compile-no-warning-as-error")
]]#

#specify different compilers for different pipelines (!!!!)
set(ENV{CC} "/usr/local/bin/clang-21")
set(ENV{CCX} "/usr/local/bin/clang++")
set(ENV{CLANGCCX} "/usr/local/bin/clang-cpp")
set(ENV{CLAZY_CHECKS} "level2")

# set tooling options in pipelines, not builds themselves
#.. linters
set(CMAKE_CXX_CLANG_TIDY ON)
set(CMAKE_CXX_CPPCHECK ON)
set(CMAKE_CXX_CPPLINT ON)
set(CMAKE_CXX_ICSTAT ON) # from CMake v4.1.0 if I got it right
#.. linkers
set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE ON)
set(CMAKE_CXX_LINK_WHAT_YOU_USE ON)
#.. specific file linker option
set_source_files_properties(main.cpp
	SKIP_LINTING
)

# test launcher injection:
#[[
set_target_property(CMAKE_CXX_COMPILER_LAUNCHER "something tbd")
set_target_property(CMAKE_CXX_LINKER_LAUNCHER "something tbd")
set_target_property(TEST_LAUNCHER "something tbd")
]]#

# enable extraction of cmake error/warning metainfo (?)
set(CTEST_USE_LAUNCHERS ON)
include(CTestUseLaunchers)

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

# Something about pipeline that looks interesting enough but I have no idea how to plug in the project yet
#[[
set(CTEST_CMAKE_GENERATOR "Ninja Multi-Config")
ctest_start()
ctest_configure()
ctest_build(CONFIG Debug)
ctest_build(CONFIG Release)
# "not possible yet"
#ctest_test(CONFIG Debug)
#ctest_test(CONFIG Release)
#ctest_package(CONFIGURATIONS Debug Release)
ctest_submit()
]]#

]==]#
