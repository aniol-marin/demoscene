set(ENV{CXXFLAGS} "-g")
# Custom report settings, they can be skipped in favor of defaults
cmake_host_system_information(RESULT user QUERY FQDN)
cmake_host_system_information(RESULT distro QUERY DISTRIB_NAME)
execute_process(
	COMMAND git branch --show-current
	OUTPUT_VARIABLE branch
)
set(CTEST_SITE "${user}@${distro}")
set(CTEST_BUILD_NAME "${branch}")
if(NOT DEFINED DASHBOARD)
	set(DASHBOARD Experimental)
endif()


# Effective report start
message(NOTICE "starting ${DASHBOARD} report")
ctest_start(${DASHBOARD})

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
ctest_read_custom_files("${CTEST_BINARY_DIRECTORY}")
ctest_build()

message(NOTICE "testing...")
ctest_read_custom_files("${CTEST_BINARY_DIRECTORY}")
ctest_test()
message(NOTICE "gathering coverage info...")
ctest_read_custom_files(${CTEST_BINARY_DIRECTORY})
ctest_coverage()
message(NOTICE "performing memcheck...")
ctest_memcheck()

message(NOTICE "submitting report")
ctest_read_custom_files("${CTEST_BINARY_DIRECTORY}")
ctest_submit()

message(NOTICE "finished submitting ${DASHBOARD} report")

