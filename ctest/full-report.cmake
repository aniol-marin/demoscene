cmake_host_system_information(RESULT user QUERY FQDN)
cmake_host_system_information(RESULT distro QUERY DISTRIB_NAME)
execute_process(
	COMMAND git branch --show-current
	OUTPUT_VARIABLE branch
)
set(CTEST_SITE "${user}@${distro}")
set(CTEST_BUILD_NAME "${branch}")

message(NOTICE "starting report")
ctest_start("Experimental")

#[[
message(NOTICE "updating for report")
ctest_update()
]]#

message(NOTICE "configuring for report")
ctest_configure(
	BUILD   ${CTEST_BINARY_DIRECTORY}
	SOURCE  ${CTEST_SOURCE_DIRECTORY}
)
message(NOTICE "building for report")
ctest_build()

message(NOTICE "testing for report")
ctest_test()
#[[
message(NOTICE "checking coverage for report")
ctest_coverage()
]]#

message(NOTICE "submitting report")
ctest_submit()
