set(MODULE_NAME imgui_wrapper)
add_module_target_transitional(${MODULE_NAME})

manage_dependency_imgui()

target_link_libraries(${MODULE_NAME} PRIVATE
	imgui
)

target_sources(${MODULE_NAME} PUBLIC
	imgui.cpp
)

