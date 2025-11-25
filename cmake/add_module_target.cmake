function(add_module_target MODULE_NAME)

	add_library(${MODULE_NAME})
	target_compile_features(${MODULE_NAME} PUBLIC cxx_std_17)

	target_include_directories( ${MODULE_NAME} PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	)
	target_compile_features(${MODULE_NAME} PUBLIC cxx_std_17)

endfunction()

function(add_module_target_transitional MODULE_NAME)

	add_library(${MODULE_NAME})
	target_compile_features(${MODULE_NAME} PUBLIC cxx_std_17)

	target_include_directories( ${MODULE_NAME} PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	)

endfunction()

function(add_module_target_no_implementation MODULE_NAME)

	#no difference
	add_module_target_transitional(${MODULE_NAME})

	target_include_directories( ${MODULE_NAME} INTERFACE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	)

endfunction()
