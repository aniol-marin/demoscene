manage_dependency_sdl()

add_module(sdl_wrapper
	IMPLEMENTATIONS
	sdl.cpp
	DEPENDENCIES
	SDL2::SDL2
	engine_definitions
)

