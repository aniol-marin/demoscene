set(MODULE_NAME demoscene)
add_executable(${MODULE_NAME})

add_subdirectory(engine)
add_subdirectory(effects)

target_link_libraries(${MODULE_NAME}
	PRIVATE effect
	PRIVATE effects
	PRIVATE engine_definitions
	PRIVATE injection
	PRIVATE input
	PRIVATE program
	PRIVATE render
	PRIVATE renderables
	PRIVATE sdl_wrapper
	PRIVATE serialization
	PRIVATE sound
	PRIVATE timeline
	PRIVATE timer
)

target_sources(${MODULE_NAME} PUBLIC
	FILE_SET demo TYPE CXX_MODULES
	FILES
	demo.cpp
)

target_sources(${MODULE_NAME} PUBLIC
	main.cpp
)

