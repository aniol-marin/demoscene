function(add_module_target MODULE_NAME)

	add_library(${MODULE_NAME})
	target_compile_features(${MODULE_NAME} PUBLIC cxx_std_20)
	if(MoleDemo_Testing_EnableCoverage)
		target_compile_options(${MODULE_NAME} PRIVATE -coverage)
		target_link_options(${MODULE_NAME} PRIVATE -coverage)
	endif()

	target_sources(${MODULE_NAME} PUBLIC
		FILE_SET CXX_MODULES
		BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
		FILES
		interface.cpp
	)

endfunction()

function(add_module_target_no_implementation MODULE_NAME)

	add_module_target(${MODULE_NAME})

	if(MoleDemo_Testing_EnableCoverage)

		target_compile_options(${MODULE_NAME} PRIVATE -coverage)
		target_link_options(${MODULE_NAME} PRIVATE -coverage)
	endif()

endfunction()

function(add_executable_target EXECUTABLE_NAME)

	add_executable(${EXECUTABLE_NAME})

	if(MoleDemo_Testing_EnableCoverage)
		target_compile_options(${EXECUTABLE_NAME} PRIVATE -coverage)
		target_link_options(${EXECUTABLE_NAME} PRIVATE -coverage)
	endif()

endfunction()
