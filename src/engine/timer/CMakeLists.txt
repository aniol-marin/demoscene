set(MODULE_NAME timer)
add_module_target(${MODULE_NAME})

target_link_libraries(${MODULE_NAME} PUBLIC
	engine_definitions
)

target_sources(${MODULE_NAME} PRIVATE
	timer.cpp
)

