include(FetchContent)
mark_as_advanced(FORCE
	FETCHCONTENT_BASE_DIR
) 

add_subdirectory(glad)
add_subdirectory(imgui)
add_subdirectory(glfw)

