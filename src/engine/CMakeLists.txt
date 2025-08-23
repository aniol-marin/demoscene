
include(${CMAKE_SOURCE_DIR}/cmake/add_module_target.cmake RESULT_VARIABLE status)
if(status)
	message(STATUS "cmake add_module_target script found")
else()
	message(SEND_ERROR "add_module_target.cmake script not found.")
endif()

set(MODULE_NAME engine)
add_module_target_transitional(${MODULE_NAME})

add_subdirectory(dependencies)

add_subdirectory(cycle)
add_subdirectory(definitions)
add_subdirectory(effect)
add_subdirectory(injection)
add_subdirectory(input)
add_subdirectory(program)
add_subdirectory(render)
add_subdirectory(renderables)
add_subdirectory(sound)
add_subdirectory(timeline)
add_subdirectory(timer)

target_link_libraries(${MODULE_NAME}
	PUBLIC effect
	PUBLIC engine_definitions
	PUBLIC injection
	PUBLIC input
	PUBLIC program
	PUBLIC render
	PUBLIC renderables
	PUBLIC sound
	PUBLIC timeline
	PUBLIC timer
)

target_sources(${MODULE_NAME} PUBLIC
	engine.cpp
)

