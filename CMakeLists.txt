cmake_minimum_required(VERSION 3.31)

project(MoleDemoScene2024 VERSION 0.0.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)
set(CMAKE_CXX_FLAGS_DEBUG "modules-ts")
set(CMAKE_CXX_FLAGS_RELEASE "modules-ts")

# Configuration options
# configure_file(config.h.in config.h)
set(CMAKE_CONFIGURATION_TYPES "Debug;Release")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_BANTAMDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -D_BANTAMRELEASE")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

add_executable(demoscene)

target_sources(demoscene PRIVATE
	FILE_SET test_module TYPE CXX_MODULES
	FILES
	test_module.cpp
)

target_sources(demoscene PRIVATE
	test.cpp
)
