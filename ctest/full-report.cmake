# Custom report settings, they can be skipped in favor of defaults
cmake_host_system_information(RESULT user QUERY FQDN)
cmake_host_system_information(RESULT distro QUERY DISTRIB_NAME)
execute_process(
	COMMAND git branch --show-current
	OUTPUT_VARIABLE branch
)
set(CTEST_SITE "${user}@${distro}")
set(CTEST_BUILD_NAME "${branch}")


# Effective report start
message(NOTICE "starting Experimental report")
ctest_start("Experimental")

#[[
message(NOTICE "updating for report")
ctest_update()
]]#

message(NOTICE "configuring...")
ctest_configure(
	BUILD   ${CTEST_BINARY_DIRECTORY}
	SOURCE  ${CTEST_SOURCE_DIRECTORY}
)
message(NOTICE "building...")
ctest_build()

message(NOTICE "testing...")
ctest_test()
#[[ TO DO add additional metrics
message(NOTICE "checking coverage for report")
ctest_coverage()
ctest_sanitizer()
ctest_memcheck()
]]#

message(NOTICE "submitting report")
ctest_submit()
