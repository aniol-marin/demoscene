set(MODULE_NAME imgui_wrapper)
add_module_target_transitional(${MODULE_NAME})

include(${CMAKE_SOURCE_DIR}/cmake/manage_dependency_imgui.cmake REQUIRED)
manage_dependency_imgui()

target_link_libraries(${MODULE_NAME} PRIVATE
	imgui
)

target_sources(${MODULE_NAME} PUBLIC
	imgui.cpp
)

