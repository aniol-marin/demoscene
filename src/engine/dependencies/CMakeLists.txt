add_subdirectory(pugi)
add_subdirectory(sdl)
add_subdirectory(raudio)

target_link_libraries(${TARGET_NAME}
	INTERFACE sdl_wrapper
	INTERFACE serialization
	INTERFACE sound
)

