set(MODULE_NAME solid)
add_module(${MODULE_NAME}
	IMPLEMENTATIONS
	Solid.cpp
)
target_link_libraries(${MODULE_NAME} PUBLIC
	effect
	engine_definitions
	timer
)

