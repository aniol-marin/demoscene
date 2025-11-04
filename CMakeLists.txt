# CMake requirements
#[[	Expected policies:
	- [CMP0076] introduced in 3.13
]]#
cmake_minimum_required(VERSION 3.13)

# Pre-project definition compilation requirements
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSION OFF)
set(GCC_EXPERTED_VERSION 11.0)

# Project definition
project(MoleDemoScene2025
	VERSION 0.0.0
	DESCRIPTION "A CPU based rendering creation"
	LANGUAGES CXX C
)

# Project requirements
if(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
	if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS GCC_EXPERTED_VERSION)
		message(FATAL_ERROR "
		incompatible compiler version.
		found:    ${DCMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}
		required: ${DCMAKE_CXX_COMPILER_ID} ${GCC_EXPERTED_VERSION}")
	endif()
else()
	#[[ TODO: add support for the right version of clang and so on ]]#
	message(FATAL_ERROR "
	this project requires GNU g++ as the main c++ compiler.
	The current selected compiler is: ${CMAKE_CXX_COMPILER_ID}")
endif()

# Project build scripts
add_subdirectory(cmake)

# Experimental features (WIP)
if(EnableExperimentalFeatures)
	message(WARNING "experimental features enabled")

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
		#NOTE: send error since generation is valid otherwise
		message(SEND_ERROR "
		IPO is still experimental!
		enable experimental features if you plan to use it")
	endif()
endif()

# Project generation info
add_subdirectory(src)

if(EnableTesting)
	message(NOTICE "enabling testing")
	include(CTest)
	enable_testing()
	add_subdirectory(test)
else()
	message(STATUS "testing not enabled")
endif()

