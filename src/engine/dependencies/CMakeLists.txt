add_subdirectory(pugi)
add_subdirectory(sdl)
add_subdirectory(raudio)

target_link_libraries(${MODULE_NAME}
	INTERFACE sdl_wrapper
	INTERFACE serialization
	INTERFACE sound
)

