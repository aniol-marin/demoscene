
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
target_sources(${EXECUTABLE_NAME} PUBLIC
	main.cpp
)
target_link_libraries(${EXECUTABLE_NAME} PRIVATE
	glfw_wrapper
	glad_wrapper
	imgui_wrapper
	editor_
)


#[[ TODO create executable cmake script
in order to encapsulate coverate logic
]]#
if(EnableTesting)
	target_compile_options(${EXECUTABLE_NAME} PRIVATE
		-coverage
	)
endif()

set(MODULE_NAME editor_)
add_module_target_transitional(${MODULE_NAME})
target_sources(${EXECUTABLE_NAME} PUBLIC
	editor.cpp
)
target_link_libraries(${MODULE_NAME} PRIVATE
	glfw_wrapper
	glad_wrapper
	imgui_wrapper
)

