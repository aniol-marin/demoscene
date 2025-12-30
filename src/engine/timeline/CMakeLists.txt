set(MODULE_NAME timeline)

add_module_target(${MODULE_NAME})

target_link_libraries( ${MODULE_NAME} PUBLIC
	cycle
	effect
	stars
	effects
	#[[
	PRIVATE effects
	serialization
	]]#
	engine_definitions
	program
	raudio
	render
	renderables
	sound
	timer
)

target_sources( ${MODULE_NAME} PRIVATE 
	timeline.cpp
)

