# CMake requirements
#[[	Expected policies:
- [CMP0076] introduced in 3.13
]]#
cmake_minimum_required(VERSION 3.13)

# Pre-project experimental requirements
#[[ not available in 3.13
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "d0edc3af-4c50-42ea-a356-e2862fe7a444")
set(CMAKE_EXPERIMENTAL_EXPORT_PACKAGE_DEPENDENCIES "1942b4fa-b2c5-4546-9385-83f254070067")
]]#
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
# TO DO add CPack definition
#include(InstallRequiredSystemLibraries)
#set(CPACK_RESOURCE_FILE_LICENSE "./LICENSE")
#set(CPACK_VERSION_MAJOR 0)
#set(CPACK_VERSION_MINOR 2)
#include(CPack)

# Early check for project requirements
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

# Load project build scripts
add_subdirectory(cmake)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/")

# Project generation info
add_subdirectory(src)
add_subdirectory(test)

