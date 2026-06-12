manage_dependency_sdl()

add_module(sdl_wrapper
	LEGACY
	IMPLEMENTATIONS
	sdl.cpp
	DEPENDENCIES
	SDL3::SDL3-static
	engine_definitions
)

