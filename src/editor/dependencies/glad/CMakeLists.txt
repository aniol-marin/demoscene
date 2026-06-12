project(mole_glad LANGUAGES C)

manage_dependency_glad()

add_module(glad_wrapper
	LEGACY
	IMPLEMENTATIONS
	glad.cpp
	DEPENDENCIES
	glfw_wrapper
	engine_definitions
	glad
)

