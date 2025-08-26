set(MODULE_NAME glfw_wrapper)
add_module_target_transitional(${MODULE_NAME})

manage_dependency_glfw()

target_link_libraries(${MODULE_NAME} PRIVATE
	glfw
	engine_definitions
)

target_sources(${MODULE_NAME} PUBLIC
	glfw.cpp
)

