
add_subdirectory(dependency_managers)

include(add_module_target.cmake QUIET)
include(add_test_target.cmake QUIET)
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

