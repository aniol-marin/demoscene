set(MODULE_NAME render)
add_module_target(${MODULE_NAME})

target_link_libraries( ${MODULE_NAME} PUBLIC
	engine_definitions
	effect
	renderables
	sdl_wrapper
)

target_sources( ${MODULE_NAME} PRIVATE
	render.cpp
)
