set(MODULE_NAME cycle)
add_module_target_transitional(${MODULE_NAME})

target_link_libraries(${MODULE_NAME}
	PRIVATE effect
	PRIVATE engine_definitions
	PRIVATE input
	PRIVATE program
	PRIVATE render
	PRIVATE renderables
	PRIVATE sdl_wrapper
)

target_sources(${MODULE_NAME} PUBLIC
	cycle.cpp
)

