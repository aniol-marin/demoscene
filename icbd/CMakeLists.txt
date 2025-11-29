
cmake_minimum_required(VERSION 4.2.0)
project(Coverage_Tests
	VERSION 0.0.0
	DESCRIPTION "A sandbox experiment"
	LANGUAGES CXX
)
enable_testing()

list(APPEND CMAKE_CXX_FLAGS "-O0 -coverage")

add_executable(target)
target_sources(target PRIVATE
	./coverage.cpp
)

