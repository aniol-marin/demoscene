
add_subdirectory(dependencies)

#[[	TO DO

	Move sandbox out of editor folder
	in order to decouple engine depencencies
	from editor ones.
]]#
if(NOT DisableAllButExperimental)
	add_subdirectory(sandbox)
endif()

set(EXECUTABLE_NAME editor)
add_executable_target(${EXECUTABLE_NAME})
target_sources(${EXECUTABLE_NAME} PUBLIC
	main.cpp
)
target_link_libraries(${EXECUTABLE_NAME} PUBLIC
	editor_
	# TO DO fix implementation depenency leakage
	imgui
	glfw_wrapper
	glad_wrapper
	imgui_wrapper
)

set(MODULE_NAME editor_)
add_module_target(${MODULE_NAME})
target_sources(${EXECUTABLE_NAME} PRIVATE
	editor.cpp
)
target_link_libraries(${MODULE_NAME} PUBLIC
	glfw_wrapper
	glad_wrapper
	imgui_wrapper
)

