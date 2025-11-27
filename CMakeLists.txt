# CMake requirements
#[[	Expected policies:
	- [CMP0076] introduced in 3.13
]]#
cmake_minimum_required(VERSION 3.13)

# Pre-project definition compilation requirements
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSION OFF)
set(GCC_EXPECTED_VERSION 11.0)
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

# Project definition
project(MoleDemoScene2025
	VERSION 0.0.0
	DESCRIPTION "A CPU based rendering creation"
	LANGUAGES CXX C
)
enable_testing()
include(CTest)

# Project requirements
if(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
	if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS GCC_EXPECTED_VERSION)
		message(FATAL_ERROR "
		incompatible compiler version.
		found:    ${DCMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}
		required: ${DCMAKE_CXX_COMPILER_ID} ${GCC_EXPECTED_VERSION}")
	endif()
else()
	#[[ TODO: add support for the right version of clang and so on ]]#
	message(FATAL_ERROR "
	this project requires GNU g++ as the main c++ compiler.
	The current selected compiler is: ${CMAKE_CXX_COMPILER_ID}")
endif()

# Project build scripts
add_subdirectory(cmake)

manage_dependency_protobuf()
add_executable(minitest main.cpp ./messages.pb.cc)
target_link_libraries(minitest PUBLIC protobuf::libprotobuf)

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
	add_subdirectory(test)
else()
	message(STATUS "testing not enabled")
endif()

#include(InstallRequiredSystemLibraries)
#set(CPACK_RESOURCE_FILE_LICENSE "./LICENSE")
#set(CPACK_VERSION_MAJOR 0)
#set(CPACK_VERSION_MINOR 2)
#include(CPack)
