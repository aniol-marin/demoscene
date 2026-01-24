include(CMakeParseArguments) # placeholder include since 3.5

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
		target_compile_options(${NAME} INTERFACE -coverage)
		target_link_options(${NAME} INTERFACE -coverage)
	endif()

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
