set(MODULE_NAME program)
add_library(${MODULE_NAME})

target_link_libraries(${MODULE_NAME}
	public engine_definitions
)

target_include_directories( ${MODULE_NAME} PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

target_sources(${MODULE_NAME} PUBLIC
	program.cpp
)

