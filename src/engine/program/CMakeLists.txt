set(MODULE_NAME program)
add_module_target_transitional(${MODULE_NAME})

target_link_libraries(${MODULE_NAME}
	PUBLIC engine_definitions
)

target_sources(${MODULE_NAME} PUBLIC
	program.cpp
)

