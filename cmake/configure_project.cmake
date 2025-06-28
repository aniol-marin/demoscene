#[[
	configure_project sets the project variables
	according to the user input.

	Configuration options are abstracted from the underlying
	CMake variables, although their underlying value is still
	used as a default. It should be always possible to skip
	this script altogether and configure all the CMake variables
	manually. Separation between this interface and the real
	CMakeCache values is achieved through marking the latter as
	advanced CCache variables
]]#
function(configure_project)

	# Compiler choice
	if(NOT DEFINED Config_Compiler)
		set(Config_Compiler
			"${CMAKE_CXX_COMPILER}"
			CACHE PATH
			"Specify the compiler to be used"
		)
	endif()
	set(CMAKE_CXX_COMPILER ${Config_Compiler}
		CACHE PATH
		"[AUTOMATICALLY REGENERATED] the effective compiler to be used"
		FORCE
	)
	mark_as_advanced(FORCE CMAKE_RUNTIME_OUTPUT_DIRECTORY)

	# Runtime files output
	if(NOT DEFINED Config_PathFor_Binaries)
		set(Config_PathFor_Binaries
			"${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}"
			CACHE PATH
			"Specify the folder where the resulting binaries will be placed"
		)
	endif()
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${Config_PathFor_Binaries}
		CACHE PATH
		"[AUTOMATICALLY REGENERATED] the effective folder where the resulting binaries will be placed"
		FORCE
	)
	mark_as_advanced(FORCE CMAKE_RUNTIME_OUTPUT_DIRECTORY)

	# Library files output
	if(NOT DEFINED Config_PathFor_Libraries)
		set(Config_PathFor_Libraries
			"${CMAKE_SOURCE_DIR}/lib/${CMAKE_BUILD_TYPE}"
			CACHE PATH
			"Specify the folder where the resulting library files will be placed"
		)
	endif()
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${Config_PathFor_Libraries}
		CACHE PATH
		"[AUTOMATICALLY REGENERATED] the effective folder where the resulting library files will be placed"
		FORCE
	)
	mark_as_advanced(FORCE CMAKE_ARCHIVE_OUTPUT_DIRECTORY)
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${Config_PathFor_Libraries}
		CACHE PATH
		"[AUTOMATICALLY REGENERATED] the effective folder where the resulting archive files will be placed"
		FORCE
	)
	mark_as_advanced(FORCE CMAKE_LIBRARY_OUTPUT_DIRECTORY)

	# Fetched Content placement
	if(NOT DEFINED Config_PathFor_Dependencies)
		set(Config_PathFor_Dependencies
			"${CMAKE_SOURCE_DIR}/external"
			CACHE PATH
			"Specify where to fetch the external dependencies"
		)
	endif()
	set(FETCHCONTENT_BASE_DIR ${Config_PathFor_Dependencies}
		CACHE PATH
		"[AUTOMATICALLY REGENERATED] the effective folder where the dependency files will be placed"
		FORCE
	)

	# FetchContent centralized declaration
	include(FetchContent)
	mark_as_advanced(FORCE
		FETCHCONTENT_BASE_DIR
		FETCHCONTENT_FULLY_DISCONNECTED
		FETCHCONTENT_QUIET
		FETCHCONTENT_UPDATES_DISCONNECTED
	)

endfunction()

