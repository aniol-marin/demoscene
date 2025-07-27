
add_subdirectory(dependencies)
add_subdirectory(sandbox)

add_executable(editor)

target_link_libraries(editor PRIVATE
	glfw_wrapper
	glad_wrapper
	imgui_wrapper
)

target_sources(editor PUBLIC
	FILE_SET editor TYPE CXX_MODULES
	FILES
	editor.cpp
)

target_sources(editor PUBLIC
	main.cpp
)
