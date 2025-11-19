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
	if(NOT DEFINED MoleDemo_EnableEditor)
		option(MoleDemo_EnableEditor "enables generation of editor tool" ON)
	endif()
	if(NOT DEFINED MoleDemo_ForceFetchedDependencies)
		option(MoleDemo_ForceFetchedDependencies "forces usage of FetchContent over locally installed packages" OFF)
	endif()
	if(NOT DEFINED MoleDemo_EnableExperimentalFeatures)
		option(MoleDemo_EnableExperimentalFeatures "enables experimental features" OFF)
	endif()
	if(NOT DEFINED MoleDemo_EnableTesting)
		option(MoleDemo_EnableTesting "enables testing targets" ON)
	endif()
	if(NOT DEFINED MoleDemo_DisableAllButExperimental)
		option(MoleDemo_DisableAllButExperimental "DISABLES regular targets" OFF)
	endif()
	if(NOT DEFINED MoleDemo_EnableInterProceduralOptimization)
		cmake_dependent_option(
			MoleDemo_EnableInterProceduralOptimization "tries to enable IPO [EXPERIMENTAL]" OFF
			MoleDemo_EnableExperimentalFeatures OFF
		)
	endif()
	if(NOT DEFINED MoleDemo_Testing_EnableCoverage)
		cmake_dependent_option(
			MoleDemo_Testing_EnableCoverage "enables test coverage" ON
			MoleDemo_EnableTesting ON
		)
	endif()

	# FetchContent centralized declaration
	include(FetchContent)
	mark_as_advanced(FORCE
		CMAKE_INSTALL_PREFIX
		FETCHCONTENT_FULLY_DISCONNECTED
		FETCHCONTENT_QUIET
		FETCHCONTENT_UPDATES_DISCONNECTED
	)
	if(NOT DEFINED FETCHCONTENT_BASE_DIR)
	mark_as_advanced(FORCE
		FETCHCONTENT_BASE_DIR
	)
	endif()

	# CTest internals
	mark_as_advanced(FORCE
		BUILD_TESTING
	)

	# Experimental features (WIP)
	if(MoleDemo_EnableExperimentalFeatures)
		message(WARNING "experimental features enabled")

		if(MoleDemo_EnableInterProceduralOptimization)
			include(CheckIPOSupported)
			check_ipo_supported(RESULT ipo_supported)
			set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ${ipo_supported})
			if(NOT ipo_supported)
				message(WARNING "Interprocedural Optimization not supported!")
			else()
				message(NOTICE "Interprocedural Optimization support enabled")
			endif()
		endif()
	else()
		if(MoleDemo_EnableInterProceduralOptimization)
			#NOTE: send error since generation is valid otherwise
			message(SEND_ERROR "
			IPO is still experimental!
			enable experimental features if you plan to use it")
		endif()
	endif()

endfunction()

