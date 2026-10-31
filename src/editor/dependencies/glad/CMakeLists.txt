add_module(glad_wrapper
	IMPLEMENTATIONS
	glad.cpp
	DEPENDENCIES
	glfw_wrapper
	engine_definitions
	glad
)

project(mole_glad LANGUAGES C)
manage_dependency_glad()

