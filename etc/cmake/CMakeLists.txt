
include(add_module_target.cmake QUIET)
include(add_test_target.cmake QUIET)
include(manage_dependencies.cmake QUIET)
manage_dependencies()

#[[
CL-style compilers do not provide libm, which is required by some dependency.
ID needs to be simulated in order to support also clang-cl

The current solution consists on creating a dummy library, which avoids linker errors.
]]#
if(MSVC OR CMAKE_CXX_SIMULATE_ID STREQUAL "MSVC")
	add_library(m INTERFACE)
endif()

include(configure_project.cmake OPTIONAL RESULT_VARIABLE status)
if(status)
	message(STATUS "cmake configure_project script found")
	configure_project()
else()
	message(WARNING "
	configure_project.cmake script not found!

	Project will be configured with default values
	and custom user config parameters will be ignored")
endif()

