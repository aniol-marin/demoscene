set(MODULE_NAME render)
add_module_target(${MODULE_NAME})

target_link_libraries( ${MODULE_NAME}
	PRIVATE engine_definitions
	PRIVATE effect
	PRIVATE renderables
	PRIVATE sdl_wrapper
)

target_sources( ${MODULE_NAME} PUBLIC
	FILE_SET render TYPE CXX_MODULES
	FILES
	render.cpp
)
