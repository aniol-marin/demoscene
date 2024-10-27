cmake_minimum_required(VERSION 3.30)

project(MoleDemoScene2024 VERSION 0.0.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)

# Configuration options
# configure_file(config.h.in config.h)
set(CMAKE_CONFIGURATION_TYPES "Debug;Release")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -MOLE_DEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -MOLE_RELEASE")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)
set(CMAKE_SOURCE_DIRECTORY ${CMAKE_BINARY_DIR}/../src)

add_executable(demoscene)

target_sources(demoscene PRIVATE
	FILE_SET demo TYPE CXX_MODULES
	FILE_SET injection TYPE CXX_MODULES
	FILES
	src/demo.cpp
	src/injection.cpp
)

target_sources(demoscene PRIVATE
	src/main.cpp
)
