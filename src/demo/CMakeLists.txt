set(MODULE_NAME demoscene)
add_executable(${MODULE_NAME})

target_link_libraries(${MODULE_NAME}
	PRIVATE engine
	PRIVATE effects
)

target_sources(${MODULE_NAME} PUBLIC
	FILE_SET demo TYPE CXX_MODULES
	FILES
	demo.cpp
)

target_sources(${MODULE_NAME} PUBLIC
	main.cpp
)

