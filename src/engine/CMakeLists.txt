
include(${CMAKE_SOURCE_DIR}/cmake/add_module_target.cmake RESULT_VARIABLE status)
if(status)
	message(STATUS "cmake add_module_target script found")
else()
	message(SEND_ERROR "add_module_target.cmake script not found.")
endif()

add_subdirectory(cycle)
add_subdirectory(definitions)
add_subdirectory(effect)
add_subdirectory(injection)
add_subdirectory(input)
add_subdirectory(program)
add_subdirectory(pugi)
add_subdirectory(raudio)
add_subdirectory(render)
add_subdirectory(renderables)
add_subdirectory(sdl)
add_subdirectory(sound)
add_subdirectory(timeline)
add_subdirectory(timer)

set(TARGET_NAME engine)
add_library(${TARGET_NAME} INTERFACE)
target_link_libraries(${TARGET_NAME}
	INTERFACE effect
	INTERFACE engine_definitions
	INTERFACE injection
	INTERFACE input
	INTERFACE program
	INTERFACE render
	INTERFACE renderables
	INTERFACE sdl_wrapper
	INTERFACE serialization
	INTERFACE sound
	INTERFACE timeline
	INTERFACE timer
)

