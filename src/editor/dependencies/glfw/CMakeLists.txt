manage_dependency_glfw()

add_module(glfw_wrapper
	IMPLEMENTATIONS
	glfw.cpp
	DEPENDENCIES
	glfw
	engine_definitions
)

