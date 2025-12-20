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
set(CMAKE_CXX_STANDARD 98)
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
- assumes any c++ compiler will comply with c++98 requirement
]]#

# Load project build scripts
add_subdirectory(cmake)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/")

# Project generation info
add_subdirectory(src)
add_subdirectory(test)

