
include(${CMAKE_SOURCE_DIR}/cmake/add_test_target.cmake RESULT_VARIABLE status)
if(status)
	message(STATUS "cmake add_test_target script found")
else()
	message(ERROR_FAIL "add_test_target.cmake script not found.
	Disable testing if this was intended")
endif()

include(${CMAKE_SOURCE_DIR}/cmake/manage_dependency_catch.cmake RESULT_VARIABLE status)
if(status)
	message(STATUS "cmake add_test_target script found")
	manage_dependency_catch()
else()
	message(FATAL_ERROR "
	manage_dependency_catch.cmake script not found.
	Test suite cannot be generated.

	Disable testing if you want to generate the rest of the project")
endif()

add_subdirectory(engine)
add_subdirectory(editor)

