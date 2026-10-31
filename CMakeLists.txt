#[[ CMake requirements	
Expected policies:
- [CMP0076] introduced in 3.13
Expected features:
- [FetchContent SOURCE_SUBDIR] introduced in 3.18
Expected experimental features:
-
Excluded releases:
- 
]]#
cmake_minimum_required(VERSION 3.18.0..4.5.0)

# Pre-project definition compilation requirements
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Project definition
project(MoleDemoScene
	VERSION 0.0.0
	DESCRIPTION "A CPU based rendering creation"
	LANGUAGES CXX
)
enable_testing()
include(CTest)

# Early check for project requirements
#[[ Compiler feature requirements and compiler adoption
- assumes any c++ compiler will comply with c++98 requirements
]]#

# Load project build scripts
add_subdirectory(etc/cmake)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/etc/cmake/modules/")

# Project generation info
add_subdirectory(src)
add_subdirectory(test)

