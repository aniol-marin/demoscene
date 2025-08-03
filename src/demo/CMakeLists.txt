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

add_custom_command(TARGET ${MODULE_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_SOURCE_DIR}/resources
		${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources
)

