set(MODULE_NAME input)
add_module_target_transitional(${MODULE_NAME})

target_link_libraries(${MODULE_NAME} PUBLIC
	engine_definitions
	sdl_wrapper
)

target_sources(${MODULE_NAME} PRIVATE 
	input.cpp
)
