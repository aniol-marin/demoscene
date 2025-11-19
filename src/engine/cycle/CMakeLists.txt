set(MODULE_NAME cycle)
add_module_target(${MODULE_NAME})

target_link_libraries(${MODULE_NAME} PUBLIC
	effect
	engine_definitions
	input
	program
	render
	renderables
	sdl_wrapper
)

target_sources(${MODULE_NAME} PRIVATE 
	cycle.cpp
)

