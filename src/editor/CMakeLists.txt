
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
add_executable(${EXECUTABLE_NAME})
#[[ TODO create executable cmake script
in order to encapsulate coverate logic
]]#
if(EnableTesting)
	target_compile_options(${EXECUTABLE_NAME} PRIVATE
		-coverage
	)
endif()

target_link_libraries(${EXECUTABLE_NAME} PRIVATE
	glfw_wrapper
	glad_wrapper
	imgui_wrapper
)

target_sources(${EXECUTABLE_NAME} PUBLIC
	editor.cpp
	main.cpp
)

