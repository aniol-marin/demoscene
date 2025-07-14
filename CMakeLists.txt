# CMake requirements
cmake_minimum_required(VERSION 3.25)

# Pre-project definition compilation requirements
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSION OFF)

# Project definition
project(MoleDemoScene2025
	VERSION 0.0.0
	DESCRIPTION "A CPU based rendering creation"
	LANGUAGES CXX C
)

# Project automated configuration
include(${CMAKE_SOURCE_DIR}/cmake/configure_project.cmake OPTIONAL RESULT_VARIABLE status)
if(status)
	message(STATUS "cmake configure_project script found")
	configure_project()
else()
	message(WARNING "
	add_module_target.cmake script not found!

	Project will be configured with default values
	and custom user config parameters will be ignored")
endif()

# User configuration options
include(CMakeDependentOption)
if(NOT DEFINED EnableEditor)
	option(EnableEditor "enables generation of editor tool" OFF)
endif()
if(NOT DEFINED EnableExperimentalFeatures)
	option(EnableExperimentalFeatures "enables experimental features" OFF)
endif()
if(NOT DEFINED EnableTesting)
	option(EnableTesting "enables testing targets" OFF)
endif()
if(NOT DEFINED EnableInterProceduralOptimization)
	option(EnableInterProceduralOptimization "tries to enable IPO [EXPERIMENTAL]" OFF)
endif()
if(NOT DEFINED DisableAllButExperimental)
	cmake_dependent_option(
		DisableAllButExperimental "DISABLES regular targets" ON
		"EnableExperimentalFeatures" OFF
	)
endif()

# Experimental features (WIP)
if(EnableExperimentalFeatures)
	message(WARNING "experimental features enabled")

	if(EnableEditor)
		message(WARNING "editor is still experimental")
		add_subdirectory(src/editor)
	endif()
	if(EnableInterProceduralOptimization)
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
	if(EnableInterProceduralOptimization)
		message(SEND_ERROR "
		IPO is still experimental!
		enable experimental features if you plan to use it")
	endif()
	if(EnableEditor)
		message(SEND_ERROR "
		editor is still experimental!
		enable experimental features if you plan to use it")
	endif()
endif()

# Project generation info
if(NOT DisableAllButExperimental)
	add_subdirectory(src)
	if(EnableTesting)
		message(NOTICE "enabling testing")
		include(CTest)
		enable_testing()
		add_subdirectory(test)
	else()
		message(STATUS "testing not enabled")
	endif()
else()
	message(WARNING "
	all non-experimental targets disabled")
endif()

