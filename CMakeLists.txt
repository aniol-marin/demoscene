# CMake requirements
cmake_minimum_required(VERSION 4.0.3..4.2.0)

# Pre-project definition compilation requirements
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "d0edc3af-4c50-42ea-a356-e2862fe7a444")
set(CMAKE_CXX_MODULE_STD ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)
set(CMAKE_CXX_EXTENSION OFF)

# Project definition
project(MoleDemoScene2025
	VERSION 0.0.0
	DESCRIPTION "A CPU based rendering creation"
	LANGUAGES CXX C
)

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

