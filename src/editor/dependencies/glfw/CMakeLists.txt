set(MODULE_NAME glfw_wrapper)
add_module_target_transitional(${MODULE_NAME})

include(${CMAKE_SOURCE_DIR}/cmake/manage_dependency_glfw.cmake REQUIRED)
manage_dependency_glfw()

target_link_libraries(${MODULE_NAME} PRIVATE
	glfw
	engine_definitions
)

target_sources(${MODULE_NAME} PUBLIC
	glfw.cpp
)

