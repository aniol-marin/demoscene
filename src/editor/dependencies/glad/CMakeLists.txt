manage_dependency_glad()

set(MODULE_NAME glad_wrapper)
add_module_target_transitional(${MODULE_NAME})

target_sources(${MODULE_NAME} PUBLIC
	glad.cpp
)

target_link_libraries(glad_wrapper
	PRIVATE glfw_wrapper
	PRIVATE glad
)

