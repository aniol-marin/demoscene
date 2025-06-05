set(MODULE_NAME engine_definitions)
add_library(${MODULE_NAME})

target_include_directories( ${MODULE_NAME} INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

target_sources( ${MODULE_NAME} PUBLIC
	definitions.cpp
)
