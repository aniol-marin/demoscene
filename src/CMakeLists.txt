set(MODULE_NAME demoscene)
add_executable(${MODULE_NAME})

add_subdirectory(engine)
add_subdirectory(effects)

target_link_libraries(${MODULE_NAME}
	#PRIVATE raudio
	PRIVATE injection
	PRIVATE engine_definitions
	PRIVATE sdl_wrapper
	PRIVATE input
)

target_sources(${MODULE_NAME} PUBLIC
	FILE_SET demo TYPE CXX_MODULES
	FILE_SET program TYPE CXX_MODULES
	FILE_SET timer TYPE CXX_MODULES
	#FILE_SET raudio TYPE CXX_MODULES
	#FILE_SET sound TYPE CXX_MODULES
	FILE_SET effects TYPE CXX_MODULES
	FILE_SET effect TYPE CXX_MODULES
	FILE_SET stars TYPE CXX_MODULES
	FILE_SET solid TYPE CXX_MODULES
	FILE_SET gradient TYPE CXX_MODULES
	FILE_SET renderables TYPE CXX_MODULES
	FILE_SET render TYPE CXX_MODULES
	FILE_SET cycle TYPE CXX_MODULES
	FILE_SET timeline TYPE CXX_MODULES
	FILES
	demo.cpp
	program.cpp
	timer.cpp
	#raudio.cpp
	#sound.cpp
	effects.cpp
	renderables.cpp
	render.cpp
	cycle.cpp
	timeline.cpp
)

target_sources(${MODULE_NAME} PUBLIC
	main.cpp
)
