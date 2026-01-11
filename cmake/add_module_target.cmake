include(CMakeParseArguments) # placeholder include since 3.5

function(add_module_target MODULE_NAME)

	message(WARNING "
	add_module_target is deprecated
	called by: ${MODULE_NAME}")

	add_library(${MODULE_NAME})
	target_compile_features(${MODULE_NAME} PUBLIC cxx_std_17)
	target_include_directories(${MODULE_NAME} INTERFACE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	)
	if(MoleDemo_Testing_EnableCoverage)
		target_compile_options(${MODULE_NAME} PRIVATE -coverage)
		target_link_options(${MODULE_NAME} PRIVATE -coverage)
	endif()

endfunction()

function(add_module_target_no_implementation NAME)

	add_library(${MODULE_NAME} INTERFACE)
	target_compile_features(${MODULE_NAME} INTERFACE cxx_std_17)
	target_include_directories( ${NAME} INTERFACE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	)
	if(MoleDemo_Testing_EnableCoverage)
		target_compile_options(${MODULE_NAME} INTERFACE -coverage)
		target_link_options(${MODULE_NAME} INTERFACE -coverage)
	endif()
endfunction()

function(add_module NAME)

	cmake_parse_arguments(
		PARSE_ARGV 1 # discouraged alternative, prefer ${ARGN} at the end
		"A"
		"HEADER_ONLY"
		""
		"IMPLEMENTATIONS;DEPENDENCIES"
		#[[ preferred alternative, although less explicit than PARSE_ARGV in this case
		${ARGN}
		]]#
	)

	if (NOT DEFINED NAME)
		message(FATAL_ERROR "
		add_module needs a library name to be provided.

		Provided name: [${NAME}]
		header only: [${A_HEADER_ONLY}]
		Provided implementations: [${A_IMPLEMENTATIONS}]
		Provided dependencies: [${A_DEPENDENCIES}]
		Provided arguments: [${ARGN}]
		")
	endif()

	if(NOT A_HEADER_ONLY)
	add_library(${NAME})
	target_compile_features(${NAME} PUBLIC cxx_std_17)
	target_sources(${NAME}
		PRIVATE ${A_IMPLEMENTATIONS}
	)
	target_link_libraries(${NAME} PUBLIC
		${A_DEPENDENCIES}
	)
	else()
	add_library(${NAME} INTERFACE)
	target_link_libraries(${NAME} INTERFACE
		${A_DEPENDENCIES}
	)
	endif()
	target_include_directories(${NAME} INTERFACE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	)

	if(MoleDemo_Testing_EnableCoverage)
		target_compile_options(${MODULE_NAME} INTERFACE -coverage)
		target_link_options(${MODULE_NAME} INTERFACE -coverage)
	endif()

endfunction()

function(add_module_target_no_implementation NAME)

	message(WARNING "
	add_module_target_no_implementation is deprecated
	use add_module(... HEADER_ONLY) instead
	called by: ${NAME}")

	add_module(${NAME} HEADER_ONLY)

endfunction()

function(add_executable_target EXECUTABLE_NAME)

	message(WARNING "
	add_executable_target is deprecated
	called by: ${EXECUTABLE_NAME}")

	add_executable(${EXECUTABLE_NAME})

	set_property(TARGET ${EXECUTABLE_NAME} PROPERTY LABELS ${EXECUTABLE_NAME})

	if(MoleDemo_Testing_EnableCoverage)
		target_compile_options(${EXECUTABLE_NAME} PRIVATE -coverage)
		target_link_options(${EXECUTABLE_NAME} PRIVATE -coverage)
	endif()

	target_include_directories( ${EXECUTABLE_NAME} INTERFACE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	)

endfunction()

function(add_mained NAME)

	cmake_parse_arguments(
		PARSE_ARGV 1 # discouraged alternative, prefer ${ARGN} at the end
		"A"
		""
		""
		"IMPLEMENTATIONS;DEPENDENCIES"
		#[[ preferred alternative, although less explicit than PARSE_ARGV in this case
		${ARGN}
		]]#
	)

	if (NOT DEFINED NAME)
		message(FATAL_ERROR "
		add_mained needs an executable name to be provided.

		Provided name: [${NAME}]
		Provided implementations: [${A_IMPLEMENTATIONS}]
		Provided dependencies: [${A_DEPENDENCIES}]
		Provided arguments: [${ARGN}]
		")
	endif()

	add_executable(${NAME})
	target_compile_features(${NAME} PUBLIC cxx_std_17)
	target_sources(${NAME}
		PRIVATE ${A_IMPLEMENTATIONS}
	)
	target_link_libraries(${NAME} PRIVATE
		${A_DEPENDENCIES}
	)

	if(MoleDemo_Testing_EnableCoverage)
		target_compile_options(${NAME} PRIVATE -coverage)
		target_link_options(${NAME} PRIVATE -coverage)
	endif()

endfunction()
