set(MODULE_NAME imgui_wrapper)
add_module_target(${MODULE_NAME})

manage_dependency_imgui()

target_link_libraries(${MODULE_NAME} PUBLIC
	imgui
	glfw_wrapper
)

target_sources(${MODULE_NAME} PRIVATE
	imgui.cpp
)

