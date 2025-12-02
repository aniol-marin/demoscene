set(MODULE_NAME stars)
add_module_target(stars)
target_sources(${MODULE_NAME} PRIVATE
	Stars.cpp
)
target_link_libraries(${MODULE_NAME} PUBLIC
	effect
	engine_definitions
	timer
)

