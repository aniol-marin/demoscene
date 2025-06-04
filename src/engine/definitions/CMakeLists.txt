set(MODULE_NAME engine_definitions)
add_library(${MODULE_NAME})

target_sources( ${MODULE_NAME} PUBLIC
	definitions.cpp
)
