include(CMakeParseArguments) # placeholder include since 3.5

# TO DO deprecate in favor of add_module
function(add_module_target MODULE_NAME)

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
		"INTERFACE"
		"INTERFACES;HEADERS;IMPLEMENTATIONS"
		#[[ preferred alternative, although less explicit than PARSE_ARGV in this case
		${ARGN}
		]]#
	)

	if (NOT DEFINED NAME)
		message(FATAL_ERROR "
		add_module needs a library name to be provided.

		Provided name: [${NAME}]
		header only: [${A_HEADER_ONLY}]
		alternative interface name: [${A_INTERFACE}]
		Provided interfaces: [${A_INTERFACES}]
		Provided headers: [${A_HEADERS}]
		Provided implementations: [${A_IMPLEMENTATIONS}]
		Provided arguments: [${ARGN}]
		")
	endif()
	if(DEFINED A_INTERFACE)
		set(interface_name ${A_INTERFACE})
	else()
		set(interface_name interface.cpp)
	endif()

	add_library(${NAME})
	target_compile_features(${NAME} PUBLIC cxx_std_17)
	target_sources(${NAME}
		PRIVATE ${A_IMPLEMENTATIONS}
	)

	target_include_directories( ${MODULE_NAME} INTERFACE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	)

	if(MoleDemo_Testing_EnableCoverage)
		target_compile_options(${MODULE_NAME} INTERFACE -coverage)
		target_link_options(${MODULE_NAME} INTERFACE -coverage)
	endif()

endfunction()

# TO DO rename, add source files as args
function(add_executable_target EXECUTABLE_NAME)

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
