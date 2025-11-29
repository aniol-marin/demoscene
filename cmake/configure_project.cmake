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

	# User configuration options
	include(CMakeDependentOption)
	if(NOT DEFINED EnableEditor)
		option(EnableEditor "enables generation of editor tool" ON)
	endif()
	if(NOT DEFINED EnableExperimentalFeatures)
		option(EnableExperimentalFeatures "enables experimental features" OFF)
	endif()
	if(NOT DEFINED MoleDemo_EnableTesting)
		option(MoleDemo_EnableTesting "enables testing targets" ON)
	endif()
	if(NOT DEFINED DisableAllButExperimental)
		option(DisableAllButExperimental "DISABLES regular targets" OFF)
	endif()
	if(NOT DEFINED EnableInterProceduralOptimization)
		cmake_dependent_option(
			EnableInterProceduralOptimization "tries to enable IPO [EXPERIMENTAL]" OFF
			"EnableExperimentalFeatures" OFF
		)
	endif()
	if(NOT DEFINED MoleDemo_Testing_EnableCoverage)
		cmake_dependent_option(
			MoleDemo_Testing_EnableCoverage "enables test coverage" ON
			MoleDemo_EnableTesting ON
		)
	endif()

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
		CMAKE_INSTALL_PREFIX
		FETCHCONTENT_BASE_DIR
		FETCHCONTENT_FULLY_DISCONNECTED
		FETCHCONTENT_QUIET
		FETCHCONTENT_UPDATES_DISCONNECTED
	)

endfunction()

