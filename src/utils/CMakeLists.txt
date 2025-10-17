include(${CMAKE_SOURCE_DIR}/cmake/add_module_target.cmake RESULT_VARIABLE status)
if(status)
	message(STATUS "cmake add_module_target script found")
else()
	message(SEND_ERROR "add_module_target.cmake script not found.")
endif()

add_subdirectory(definitions)

