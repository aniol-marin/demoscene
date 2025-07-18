
add_subdirectory(dependencies)

add_executable(editor)

target_link_libraries(editor PRIVATE
	glfw_wrapper
	glad_wrapper
	imgui_wrapper
)

target_sources(editor PUBLIC
	main.cpp
)
