#[[ CMake requirements	
Expected policies:
- [CMP0154] introduced in 3.28
- [CMP0076] introduced in 3.13
Expected features:
- [FetchContent SOURCE_SUBDIR] introduced in 3.18
- [FILE SETS] introduced in 3.23
- [CXX MODULES] introduced in 3.30
- set(CACHE{name} ...) syntax, introduced in 4.2
Expected experimental features:
- [IMPORT STD] introduced in 3.30, last breaking change: 4.3.0-rc2
- [EXPORT PACKAGE DEPENDENCIES] introduced in 3.29, last breaking change: 4.1.0-rc4
Excluded releases
- 4.3.0: affected by issues resolved and explained in commit c68b587
]]#
cmake_minimum_required(VERSION 4.3.1..4.3.2)

# Pre-project experimental requirements
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "451f2fe2-a8a2-47c3-bc32-94786d8fc91b")
set(CMAKE_EXPERIMENTAL_EXPORT_PACKAGE_DEPENDENCIES "1942b4fa-b2c5-4546-9385-83f254070067")
# Pre-project definition compilation requirements
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_MODULE_STD ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)
set(CMAKE_CXX_EXTENSION OFF)
set(CACHE{MoleDemo_Transfer_Test}
	TYPE STRING
	HELP "attempt at using new cache syntax"
	FORCE
	VALUE "this is a mock value string"
)

# Project definition
project(MoleDemoScene2025
	VERSION 0.0.0
	DESCRIPTION "A CPU based rendering creation"
	LANGUAGES CXX C
)
enable_testing()
include(CTest)

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
set(GCC_EXPECTED_VERSION 14.1)
set(CLANG_EXPECTED_VERSION 17.0)
set(MSVC_EXPECTED_VERSION 19.34)
if(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" AND ${CMAKE_CXX_COMPILER_VERSION} VERSION_LESS ${GCC_EXPECTED_VERSION})
	message(FATAL_ERROR "
	incompatible compiler version.
	found:    ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}
	required: ${CMAKE_CXX_COMPILER_ID} ${GCC_EXPECTED_VERSION}")
elseif (${CMAKE_CXX_COMPILER_ID} MATCHES "Clang" AND ${CMAKE_CXX_COMPILER_VERSION} VERSION_LESS ${CLANG_EXPECTED_VERSION})
	message(FATAL_ERROR "
	incompatible compiler version.
	found:    ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}
	required: ${CMAKE_CXX_COMPILER_ID} ${CLANG_EXPECTED_VERSION}")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC AND ${CMAKE_CXX_COMPILER_VERSION} VERSION_LESS ${MSVC_EXPECTED_VERSION})
	message(FATAL_ERROR "
	incompatible compiler version.
	found:    ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}
	required: ${CMAKE_CXX_COMPILER_ID} ${MSVC_EXPECTED_VERSION}")
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
	message(STATUS "c++ compiler validated")
else()
	message(FATAL_ERROR "
	this version of the project requires one of the following validated c++ compilers:
	- GCC   version ${GCC_EXPECTED_VERSION}
	- Clang version ${CLANG_EXPECTED_VERSION}
	- MSVC  version ${MSVC_EXPECTED_VERSION}
	used compiler instead:
	- ${CMAKE_CXX_COMPILER_ID} version ${CMAKE_CXX_COMPILER_VERSION}")
endif()

# Load project build scripts
add_subdirectory(cmake)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/")

# Project generation info
add_subdirectory(src)
add_subdirectory(test)

