manage_dependency_glad()

add_module(glad_wrapper
	IMPLEMENTATIONS
	glad.cpp
	DEPENDENCIES
	glfw_wrapper
	engine_definitions
	glad
)

