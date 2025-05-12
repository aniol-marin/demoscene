set(MODULE_NAME engine_definitions)

add_library(${MODULE_NAME}
	definitions.cpp
)

target_include_directories( ${MODULE_NAME} PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

