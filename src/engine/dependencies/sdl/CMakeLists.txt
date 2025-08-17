set(MODULE_NAME sdl_wrapper)
add_module_target(${MODULE_NAME})

include(${CMAKE_SOURCE_DIR}/cmake/manage_dependency_sdl.cmake REQUIRED)
manage_dependency_sdl()

target_link_libraries( ${MODULE_NAME}
	PRIVATE SDL2::SDL2
	PRIVATE engine_definitions
)

target_sources(${MODULE_NAME} PUBLIC
	#[[ forward compatibility
	FILE_SET sdl_wrapper TYPE CXX_MODULES
	FILES
	]]#
	sdl.cpp
)


