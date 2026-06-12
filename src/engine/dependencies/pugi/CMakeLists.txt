manage_dependency_pugixml()

add_module(serialization
	LEGACY
	IMPLEMENTATIONS
	node.cpp
	tree.cpp
	DEPENDENCIES
	pugixml
)

