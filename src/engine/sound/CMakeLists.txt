set(MODULE_NAME sound)
add_module_target(${MODULE_NAME})

target_link_libraries(${MODULE_NAME} PUBLIC
	raudio_wrapper
)

target_sources(${MODULE_NAME} PRIVATE
	sound.cpp
)
