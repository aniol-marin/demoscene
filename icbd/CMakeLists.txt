
cmake_minimum_required(VERSION 4.2.0)
project(Coverage_Tests
	VERSION 0.0.0
	DESCRIPTION "A sandbox experiment"
	LANGUAGES CXX
)
enable_testing()

add_executable(target)
target_sources(target PRIVATE
	./coverage.cpp
)
target_compile_options(target PRIVATE -coverage)
target_link_options(target PRIVATE -coverage)

include(CTest)
add_test(NAME coverage COMMAND $<TARGET_FILE:target>)

