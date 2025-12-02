#TO DO handle other paths
set(INSTALLED_DIR /usr/local/)

if(EXISTS ${INSTALLED_DIR}/include/imgui)

	if(NOT TARGET imgui)
		add_library(imgui STATIC IMPORTED)
		target_include_directories(imgui INTERFACE
			${INSTALLED_DIR}/include/imgui
			${INSTALLED_DIR}/include/imgui/backends
		)
		set_target_properties(imgui
			PROPERTIES
			IMPORTED_LOCATION ${INSTALLED_DIR}/lib/libimgui.a
			INTERFACE_LINK_LIBRARIES glfw
		)
	endif()

	set(imgui_DIR "/usr/local/lib/")
	set(imgui_INCLUDE_DIR "/usr/local/include/imgui/")
	set(imgui_FOUND ON)

	mark_as_advanced(
		imgui_FOUND
		imgui_DIR
		imgui_INCLUDE_DIR
	)
endif()

