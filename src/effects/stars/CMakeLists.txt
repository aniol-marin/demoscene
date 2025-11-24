set(MODULE_NAME stars)
add_module_target_transitional(stars)
target_sources(${MODULE_NAME} PUBLIC
	Stars.cpp
)
target_link_libraries(${MODULE_NAME}
	PUBLIC effect
	PUBLIC engine_definitions
	PUBLIC timer
)

