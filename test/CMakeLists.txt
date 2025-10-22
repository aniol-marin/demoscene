
include(${CMAKE_SOURCE_DIR}/cmake/add_test_target.cmake RESULT_VARIABLE status)
if(status)
	message(STATUS "cmake add_test_target script found")
else()
	message(ERROR_FAIL "add_test_target.cmake script not found.
	Disable testing if this was intended")
endif()

manage_dependency_catch()

if(NOT DisableAllButExperimental)
add_subdirectory(engine)
endif()
if(EnableEditor)
add_subdirectory(editor)
endif()

