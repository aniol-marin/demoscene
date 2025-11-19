set(MODULE_NAME engine_definitions)

add_module(${MODULE_NAME}
	INTERFACES
	type_aliases.cpp
	IMPLEMENTATIONS
	definitions.cpp
	color.cpp
	screen.cpp
)

