set(MODULE_NAME engine_definitions)
add_module_target(${MODULE_NAME})

target_sources( ${MODULE_NAME} PUBLIC
	definitions.cpp
	color.cpp
	screen.cpp
)

