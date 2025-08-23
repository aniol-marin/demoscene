
add_subdirectory(dependencies)

#[[	TO DO

	Move sandbox out of editor folder
	in order to decouple engine depencencies
	from editor ones.
]]#
if(NOT DisableAllButExperimental)
	add_subdirectory(sandbox)
endif()

add_executable(editor)

target_link_libraries(editor PRIVATE
	glfw_wrapper
	glad_wrapper
	imgui_wrapper
)

set(MODULE_NAME editor)
add_module_target_transitional(${MODULE_NAME})

target_sources(${MODULE_NAME} PUBLIC
	editor.cpp
	main.cpp
)

