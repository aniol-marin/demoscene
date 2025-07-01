set(MODULE_NAME engine_definitions)

add_module_target(${MODULE_NAME})

target_include_directories( ${MODULE_NAME} PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

target_sources( ${MODULE_NAME} PRIVATE
	definitions.cpp
)

