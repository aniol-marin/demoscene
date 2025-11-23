set(TEST_TARGET test-timeline)

add_test_target(${TEST_TARGET})

target_link_libraries(${TEST_TARGET}
	PRIVATE timeline
	cycle
	effect
	#[[
	effects
	]]#
	engine_definitions
	input
	program
	#[[
	raudio
	]]#
	render
	renderables
	sdl_wrapper
	serialization
	sound
	timer
)

