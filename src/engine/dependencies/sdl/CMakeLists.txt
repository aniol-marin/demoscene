set(MODULE_NAME sdl_wrapper)
add_module_target(${MODULE_NAME})

manage_dependency_sdl()

target_link_libraries( ${MODULE_NAME} PUBLIC
	SDL2::SDL2
	engine_definitions
)

target_sources(${MODULE_NAME} PRIVATE
	sdl.cpp
)

