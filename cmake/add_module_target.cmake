function(add_module_target MODULE_NAME)

	add_library(${MODULE_NAME})

endfunction()

function(add_module_target_transitional MODULE_NAME)

	add_library(${MODULE_NAME})

	#[[
	target_sources(${MODULE_NAME} PUBLIC
		FILE_SET ${MODULE_NAME} TYPE CXX_MODULES
		FILES
		interface.cpp
	)
	]]#

endfunction()

function(add_module_target_no_implementation MODULE_NAME)

	add_library(${MODULE_NAME} INTERFACE)

endfunction()
