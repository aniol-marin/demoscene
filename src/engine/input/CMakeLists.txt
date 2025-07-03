set(MODULE_NAME input)
add_module_target(${MODULE_NAME})

target_link_libraries(${MODULE_NAME}
	PRIVATE engine_definitions
	PRIVATE sdl_wrapper
)

target_sources(${MODULE_NAME} PRIVATE
	input.cpp
)
