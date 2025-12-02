set(MODULE_NAME renderables)
add_module_target(${MODULE_NAME})

target_link_libraries(${MODULE_NAME}
	PRIVATE engine_definitions
	PRIVATE effect
)

target_sources(${MODULE_NAME} PUBLIC
	renderables.cpp
)

