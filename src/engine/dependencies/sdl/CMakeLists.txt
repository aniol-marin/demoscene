manage_dependency_sdl()

add_module(sdl_wrapper
	IMPLEMENTATIONS
	sdl.cpp
	DEPENDENCIES
	SDL3::SDL3-static
	SDL3_mixer
	engine_definitions
)

