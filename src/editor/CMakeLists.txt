
add_subdirectory(dependencies)

#[[	TO DO

	Move sandbox out of editor folder
	in order to decouple engine depencencies
	from editor ones.
]]#
if(NOT DisableAllButExperimental)
	add_subdirectory(sandbox)
endif()

add_mained(editor
	IMPLEMENTATIONS
	main.cpp
	DEPENDENCIES
	editor_
	# TO DO fix implementation depenency leakage
	imgui
	glfw_wrapper
	glad_wrapper
	imgui_wrapper
)

add_module(editor_
	IMPLEMENTATIONS
	editor.cpp
	DEPENDENCIES
	glfw_wrapper
	glad_wrapper
	imgui_wrapper
)

