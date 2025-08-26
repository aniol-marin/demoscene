set(MODULE_NAME engine_definitions)
add_module_target_transitional(${MODULE_NAME})

target_sources( ${MODULE_NAME} PUBLIC
	definitions.cpp
)

