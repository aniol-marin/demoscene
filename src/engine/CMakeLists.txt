add_module(engine
	IMPLEMENTATIONS
	engine.cpp
	DEPENDENCIES
	effect
	engine_definitions
	injection
	input
	program
	render
	renderables
	sound
	timeline
	timer
)


add_subdirectory(dependencies)

add_subdirectory(cycle)
add_subdirectory(effect)
add_subdirectory(injection)
add_subdirectory(input)
add_subdirectory(program)
add_subdirectory(render)
add_subdirectory(renderables)
add_subdirectory(sound)
add_subdirectory(timeline)
add_subdirectory(timer)

