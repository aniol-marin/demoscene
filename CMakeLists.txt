#[[ CMake requirements	
Expected policies:
- [CMP0154] introduced in 3.28
- [CMP0076] introduced in 3.13
Expected features:
- [FILE SETS] introduced in 3.23
- [CXX MODULES] introduced in 3.30
Expected experimental features:
- [IMPORT STD] introduced in 3.30, last breaking change: 4.0.3
- [EXPORT PACKAGE DEPENDENCIES] introduced in 3.29, last breaking change: 4.1.0-rc4
]]#
cmake_minimum_required(VERSION 4.1.0..4.2.0)

# Pre-project experimental requirements
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "d0edc3af-4c50-42ea-a356-e2862fe7a444")
set(CMAKE_EXPERIMENTAL_EXPORT_PACKAGE_DEPENDENCIES "1942b4fa-b2c5-4546-9385-83f254070067")
# Pre-project definition compilation requirements
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_MODULE_STD ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)
set(CMAKE_CXX_EXTENSION OFF)
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

# Project definition
project(MoleDemoScene2025
	VERSION 0.0.0
	DESCRIPTION "A CPU based rendering creation"
	LANGUAGES CXX
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
#[[ Compiler feature requirements and compiler adoption
- [CPP Modules Scanning]
	- g++: 14.1
	- clang++: 17.0
	- MSVC: 19.34
- [c++26 current draft support]
	- g++: trunk (partial since 14)
	- clang++: trunk (partial since 17.0)
	- MSVC: unsupported
]]#
set(GCC_EXPERTED_VERSION 14.1)
if(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
	if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS GCC_EXPECTED_VERSION)
		message(FATAL_ERROR "
		incompatible compiler version.
		found:    ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}
		required: ${CMAKE_CXX_COMPILER_ID} ${GCC_EXPECTED_VERSION}")
	endif()
else()
	#[[ TODO: add support for the right version of clang and so on ]]#
	message(FATAL_ERROR "
	this version of the project requires one of the following c++ compilers:
	- GNU  version ${GCC_EXPECTED_VERSION}
	used compiler instead:
	- ${CMAKE_CXX_COMPILER_ID} version ${CMAKE_CXX_COMPILER_VERSION}")
endif()

# Load project build scripts
add_subdirectory(cmake)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/")

# Project generation info
add_subdirectory(src)
add_subdirectory(test)

