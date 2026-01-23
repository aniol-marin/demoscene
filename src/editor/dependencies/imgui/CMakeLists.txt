manage_dependency_imgui()

add_module(imgui_wrapper
	IMPLEMENTATIONS
	imgui.cpp
	DEPENDENCIES
	imgui
	glfw_wrapper
)

