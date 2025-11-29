# CMake requirements
cmake_minimum_required(VERSION 4.0.3..4.2.0)

# Pre-project definition compilation requirements
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "d0edc3af-4c50-42ea-a356-e2862fe7a444")
set(CMAKE_CXX_MODULE_STD ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)
set(CMAKE_CXX_EXTENSION OFF)
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
	set(GCC_EXPERTED_VERSION 14.2)
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

# Load project build scripts
add_subdirectory(cmake)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/")

# Project generation info
add_subdirectory(src)
add_subdirectory(test)


