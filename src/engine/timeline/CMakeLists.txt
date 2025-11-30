set(MODULE_NAME timeline)

add_module_target_transitional(${MODULE_NAME})

target_link_libraries( ${MODULE_NAME} PUBLIC
	cycle
	effect
	stars
	effects
	#[[
	PRIVATE effects
	]]#
	engine_definitions
	program
	raudio
	render
	renderables
	serialization
	sound
	timer
)

target_sources( ${MODULE_NAME} PRIVATE 
	timeline.cpp
)

