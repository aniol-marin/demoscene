set(MODULE_NAME timeline)

add_module_target_transitional(${MODULE_NAME})

target_link_libraries( ${MODULE_NAME}
	PRIVATE cycle
	PRIVATE effect
	PRIVATE effects
	PRIVATE engine_definitions
	PRIVATE program
	PRIVATE raudio
	PRIVATE render
	PRIVATE renderables
	PRIVATE serialization
	PRIVATE sound
	PRIVATE timer
)

target_sources( ${MODULE_NAME} PUBLIC
	timeline.cpp
)

