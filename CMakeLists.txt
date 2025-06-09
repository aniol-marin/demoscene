cmake_minimum_required(VERSION 3.25)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSION OFF)

project(MoleDemoScene2025
	VERSION 0.0.0
	DESCRIPTION "A CPU based rendering creation"
	LANGUAGES CXX
)

option(EnableTesting "enables testing targets" OFF)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

#[[
include(CheckIPOSupported)
check_ipo_supported(RESULT ipo_supported)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ${ipo_supported})
]]#

add_subdirectory(src)

if(EnableTesting)
	message(NOTICE "enabling testing")
	include(CTest)
	enable_testing()
	add_subdirectory(test)
else()
	message(STATUS "testing not enabled")
endif()

