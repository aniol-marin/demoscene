set(MODULE_NAME injection)
add_module_target_transitional(${MODULE_NAME})

target_sources(${MODULE_NAME} PUBLIC
	injection.cpp
)

