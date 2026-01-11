include(CMakeParseArguments) # placeholder include since 3.5

function(add_module_target MODULE_NAME)

	message(WARNING "
	add_module_target is deprecated
	called by: ${MODULE_NAME}")

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

function(add_module NAME)

	cmake_parse_arguments(
		PARSE_ARGV 1 # discouraged alternative, prefer ${ARGN} at the end
		"A"
		"HEADER_ONLY"
		"INTERFACE"
		"INTERFACES;HEADERS;IMPLEMENTATIONS;DEPENDENCIES"
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
		Provided dependencies: [${A_DEPENDENCIES}]
		Provided arguments: [${ARGN}]
		")
	endif()
	if(DEFINED A_INTERFACE)
		set(interface_name ${A_INTERFACE})
	else()
		set(interface_name interface.cpp)
	endif()

	add_library(${NAME})
	target_compile_features(${NAME} PUBLIC cxx_std_20)
	target_sources(${NAME}
		PRIVATE ${A_IMPLEMENTATIONS}

		PUBLIC FILE_SET CXX_MODULES
		BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
		FILES ${interface_name} ${A_INTERFACES}

		PUBLIC FILE_SET HEADERS
		BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
		FILES ${A_HEADERS}
	)
	target_link_libraries(${NAME} PUBLIC
		${A_DEPENDENCIES}
	)

	if(MoleDemo_Testing_EnableCoverage)
		target_compile_options(${NAME} PRIVATE -coverage)
		target_link_options(${NAME} PRIVATE -coverage)
	endif()

endfunction()

function(add_module_target_no_implementation NAME)

	message(WARNING "
	add_module_target_no_implementation is deprecated
	called by: ${NAME}")

	add_module_target(${NAME})

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
	target_compile_features(${NAME} PUBLIC cxx_std_20)
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
