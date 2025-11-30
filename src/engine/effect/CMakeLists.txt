set(MODULE_NAME effect)
add_module_target_transitional(${MODULE_NAME})

target_link_libraries(${MODULE_NAME} PUBLIC
	engine_definitions
	timer
)

target_sources(${MODULE_NAME} PRIVATE
	Effect.cpp
)

