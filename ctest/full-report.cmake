cmake_minimum_required(VERSION 3.13)

set(ENV{CXXFLAGS} "-g")
# Custom report settings, they can be skipped in favor of defaults
if(NOT DEFINED USER)
	cmake_host_system_information(RESULT user QUERY FQDN)
	set(USER ${user})
endif()
cmake_host_system_information(RESULT distro QUERY DISTRIB_NAME)
if(distro MATCHES "^$")
	cmake_host_system_information(RESULT distro QUERY OS_NAME)
endif()
execute_process(
	COMMAND git branch --show-current
	OUTPUT_VARIABLE branch
)
set(CTEST_SITE "${USER}@${distro}")
set(CTEST_BUILD_NAME "${branch}")
if(NOT DEFINED DASHBOARD)
	set(MODEL Experimental)
else()
	set(MODEL ${DASHBOARD})
endif()
if(NOT DEFINED CTEST_COVERAGE_COMMAND)
	set(CTEST_COVERAGE_COMMAND gcov)
endif()
if(NOT DEFINED CTEST_MEMORYCHECK_COMMAND)
	set(CTEST_MEMORYCHECK_COMMAND valgrind)
endif()
set(CTEST_LABELS_FOR_SUBPROJECTS
	demoscene
)


# Effective report start
message(NOTICE "starting ${MODEL} report")
ctest_start(${MODEL})

if(FORCE_UPDATE)
	message(NOTICE "updating repository for report")
	ctest_update()
endif()

message(NOTICE "configuring...")
ctest_configure(
	BUILD   ${CTEST_BINARY_DIRECTORY}
	SOURCE  ${CTEST_SOURCE_DIRECTORY}
)
message(NOTICE "building...")
ctest_build()

message(NOTICE "testing...")
ctest_test()
message(NOTICE "gathering coverage info...")
ctest_coverage()
message(NOTICE "performing memcheck...")
ctest_memcheck()

message(NOTICE "submitting report")
ctest_submit(
    RETRY_COUNT "3"
    RETRY_DELAY "5"
)

message(NOTICE "finished submitting ${DASHBOARD} report")

