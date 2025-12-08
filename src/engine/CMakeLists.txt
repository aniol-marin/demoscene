set(MODULE_NAME engine)
add_module_target(${MODULE_NAME})
add_module_target(mole::${MODULE_NAME} ALIAS ${MODULE_NAME})

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

target_link_libraries(${MODULE_NAME} PUBLIC
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

target_sources(${MODULE_NAME} PRIVATE
	engine.cpp
)

