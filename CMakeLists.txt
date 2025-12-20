#[[ CMake requirements	
Expected policies:
- [CMP0154] introduced in 3.28
- [CMP0076] introduced in 3.13
Expected features:
-
Expected experimental features:
-
]]#
cmake_minimum_required(VERSION 3.13..4.2.1)

# Pre-project definition compilation requirements
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSION OFF)
set(CMAKE_COMPILE_WARNING_AS_ERROR OFF)

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
#[[ Compiler feature requirements and compiler adoption
- [c++17 support]
	- g++: 4.8.1
	- clang++: 3.3
	- MSVC: 15.7
]]#
set(GCC_EXPECTED_VERSION 4.8.1)
set(CLANG_EXPECTED_VERSION 3.3)
set(MSVC_EXPECTED_VERSION 15.7)
if(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
	if(${CMAKE_CXX_COMPILER_VERSION} VERSION_LESS ${GCC_EXPECTED_VERSION})
		message(FATAL_ERROR "
		incompatible compiler version.
		found:    ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}
		required: ${CMAKE_CXX_COMPILER_ID} ${GCC_EXPECTED_VERSION}")
	endif()
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
	message(WARNING "
		Support with the current compiler is still highly experimental.
		found:    ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}
		required: ${CMAKE_CXX_COMPILER_ID} ${GCC_EXPECTED_VERSION}")
else()
	#[[ TODO: add support for the right version of clang and so on ]]#
	message(FATAL_ERROR "
	this version of the project requires one of the following c++ compilers:
	- GNU  version ${GCC_EXPECTED_VERSION}
	- MSVC version ${MSVC_EXPECTED_VERSION}
	used compiler instead:
	- ${CMAKE_CXX_COMPILER_ID} version ${CMAKE_CXX_COMPILER_VERSION}")
endif()

# Load project build scripts
add_subdirectory(cmake)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/")

# Project generation info
add_subdirectory(src)
add_subdirectory(test)

