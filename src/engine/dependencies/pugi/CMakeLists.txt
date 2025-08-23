set(MODULE_NAME serialization)
add_module_target_transitional(${MODULE_NAME})

manage_dependency_pugixml()

target_link_libraries( ${MODULE_NAME}
	PUBLIC pugixml
	PUBLIC engine_definitions
)

target_sources(${MODULE_NAME} PUBLIC
	pugi.cpp
)

