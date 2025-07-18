
FetchContent_Declare(
	imgui
	EXCLUDE_FROM_ALL
	GIT_REPOSITORY https://github.com/ocornut/imgui.git
	GIT_TAG 4806a1924ff6181180bf5e4b8b79ab4394118875 # v1.91.9b-docking
)
FetchContent_MakeAvailable(imgui)

mark_as_advanced(FORCE
	FETCHCONTENT_UPDATES_DISCONNECTED_IMGUI
	FETCHCONTENT_SOURCE_DIR_IMGUI
) 

add_library(imgui_wrapper)
target_sources(imgui_wrapper PUBLIC
	FILE_SET imgui_wrapper TYPE CXX_MODULES
	FILES
	imgui.cpp
)

target_link_libraries(imgui_wrapper
	PRIVATE imgui
)

