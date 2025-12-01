set(MODULE_NAME serialization)
add_module_target(${MODULE_NAME})

manage_dependency_pugixml()

target_link_libraries( ${MODULE_NAME}
	pugixml
)

target_sources(${MODULE_NAME} PUBLIC
	node.cpp
	tree.cpp
)

