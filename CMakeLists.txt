cmake_minimum_required(VERSION 4.0.2) # actually from 802f261d629e5f51213385716824a0423d063624 so bump to 4.0.3 once tag is created

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "d0edc3af-4c50-42ea-a356-e2862fe7a444")
set(CMAKE_CXX_MODULE_STD ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)
set(CMAKE_CXX_EXTENSION OFF)

project(MoleDemoScene2025
	VERSION 0.0.0
	DESCRIPTION "A CPU based rendering creation"
	LANGUAGES CXX
)

option(EnableTesting:BOOL "enables testing targets" OFF)

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

