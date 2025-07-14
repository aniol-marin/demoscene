set(MODULE_NAME effect)
add_module_target(${MODULE_NAME})

target_link_libraries(${MODULE_NAME}
	PUBLIC engine_definitions
	PUBLIC timer
)

target_sources(${MODULE_NAME} PUBLIC
	#[[ forward compatibility
	FILE_SET ${MODULE_NAME} TYPE CXX_MODULES
	FILES
	]]#
	Effect.cpp
)
