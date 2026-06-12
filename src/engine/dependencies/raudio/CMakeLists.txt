manage_dependency_raudio()

add_module(raudio_wrapper
	LEGACY
	IMPLEMENTATIONS
	raudio.cpp
	DEPENDENCIES
	raudio
	engine_definitions
)

