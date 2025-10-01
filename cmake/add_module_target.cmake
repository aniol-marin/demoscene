function(add_module_target MODULE_NAME)

	add_library(${MODULE_NAME})

endfunction()

function(add_module_target_transitional MODULE_NAME)

	add_library(${MODULE_NAME})

	if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}interface.cpp")
		target_sources(${MODULE_NAME} PUBLIC
			FILE_SET ${MODULE_NAME} TYPE CXX_MODULES
			FILES
			interface.cpp
		)
	else()
		message(WARNING "didn't find module interface file")
	endif()

endfunction()

function(add_module_target_no_implementation MODULE_NAME)

	add_library(${MODULE_NAME} INTERFACE)

endfunction()
