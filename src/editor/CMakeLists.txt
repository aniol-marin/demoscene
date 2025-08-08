
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

target_sources(editor PUBLIC
	#[[ forward compatibility
	FILE_SET editor TYPE CXX_MODULES
	FILES
	]]#
	editor.cpp
)

target_sources(editor PUBLIC
	main.cpp
)

