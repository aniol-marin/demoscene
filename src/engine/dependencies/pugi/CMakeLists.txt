manage_dependency_pugixml()

add_module(serialization
	IMPLEMENTATIONS
	node.cpp
	tree.cpp
	DEPENDENCIES
	pugixml
)

