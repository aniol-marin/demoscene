set(MODULE_NAME temp)
#[[
set(MODULE_NAME demoscene)
add_executable(${MODULE_NAME})
]]#
add_library(temp)

add_subdirectory(engine)
add_subdirectory(loaders)
#[[
#add_subdirectory(effects)
]]#

target_link_libraries(${MODULE_NAME}
	engine_definitions
	loaders
	pugi_wrapper
	#[[
	PRIVATE injection
	PRIVATE engine_definitions
	PRIVATE sdl_wrapper
	PRIVATE input
	PRIVATE sound
	PRIVATE timer
	PRIVATE pugi_wrapper
	]]#
)

#[[
target_sources(${MODULE_NAME} PRIVATE
	FILE_SET demo TYPE CXX_MODULES
	FILE_SET program TYPE CXX_MODULES
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
	effects.cpp
	renderables.cpp
	render.cpp
	cycle.cpp
	timeline.cpp
)

]]#
target_sources(${MODULE_NAME} PRIVATE
	program.cpp
#[[
	main.cpp
]]#
)

