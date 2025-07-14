set(MODULE_NAME engine_definitions)

add_module_target(${MODULE_NAME})

target_sources( ${MODULE_NAME} PUBLIC
	#[[ forward compatibility
	FILE_SET definitions TYPE CXX_MODULES
	FILES
	]]#
	definitions.cpp
)

