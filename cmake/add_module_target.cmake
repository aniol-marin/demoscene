function(add_module_target MODULE_NAME)

	add_library(${MODULE_NAME})

	target_include_directories( ${MODULE_NAME} PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	)

endfunction()

function(add_module_target_transitional MODULE_NAME)

	add_library(${MODULE_NAME})

	target_include_directories( ${MODULE_NAME} PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	)

endfunction()
