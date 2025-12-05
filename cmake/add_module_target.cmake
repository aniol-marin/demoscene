function(add_module_target MODULE_NAME)

	add_library(${MODULE_NAME})
	target_compile_features(${MODULE_NAME} PUBLIC cxx_std_17)

	target_include_directories( ${MODULE_NAME} PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	)
	if(MoleDemo_Testing_EnableCoverage)
		target_compile_options(${MODULE_NAME} PRIVATE -coverage)
		target_link_options(${MODULE_NAME} PRIVATE -coverage)
	endif()

endfunction()

function(add_module_target_no_implementation MODULE_NAME)

	add_library(${MODULE_NAME} INTERFACE)

	target_include_directories( ${MODULE_NAME} INTERFACE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	)
	if(MoleDemo_Testing_EnableCoverage)
		target_compile_options(${MODULE_NAME} INTERFACE -coverage)
		target_link_options(${MODULE_NAME} INTERFACE -coverage)
	endif()

endfunction()

function(add_executable_target EXECUTABLE_NAME)

	add_executable(${EXECUTABLE_NAME})

	if(MoleDemo_Testing_EnableCoverage)
		target_compile_options(${EXECUTABLE_NAME} PRIVATE -coverage)
		target_link_options(${EXECUTABLE_NAME} PRIVATE -coverage)
	endif()

	target_include_directories( ${EXECUTABLE_NAME} INTERFACE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	)

endfunction()
