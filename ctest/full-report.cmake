cmake_minimum_required(VERSION 4.2.1)

set(ENV{CXXFLAGS} "-g")
# Custom report settings, they can be skipped in favor of defaults
cmake_host_system_information(RESULT user QUERY FQDN)
cmake_host_system_information(RESULT distro QUERY DISTRIB_NAME)
execute_process(
	COMMAND git branch --show-current
	OUTPUT_VARIABLE branch
)
if(NOT DEFINED USER)
	set(USER ${user})
endif()
set(CTEST_SITE "${USER}@${distro}")
set(CTEST_BUILD_NAME "${branch}")
if(NOT DEFINED DASHBOARD)
	set(MODEL Experimental)
else()
	set(MODEL ${DASHBOARD})
endif()
if(NOT DEFINED ${CTEST_COVERAGE_COMMAND})
	set(CTEST_COVERAGE_COMMAND /usr/bin/gcov)
endif()
if(NOT DEFINED ${CTEST_MEMORYCHECK_COMMAND})
	set(CTEST_MEMORYCHECK_COMMAND /usr/bin/valgrind)
endif()
set(CTEST_LABELS_FOR_SUBPROJECTS
	demoscene
	editor
	sandbox
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

