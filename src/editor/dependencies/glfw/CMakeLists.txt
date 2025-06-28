
FetchContent_Declare(
	glfw
	EXCLUDE_FROM_ALL
	GIT_REPOSITORY https://github.com/glfw/glfw.git
	GIT_TAG 7b6aead9fb88b3623e3b3725ebb42670cbe4c579 # v3.4
)
FetchContent_MakeAvailable(glfw)

mark_as_advanced(FORCE
	FETCHCONTENT_UPDATES_DISCONNECTED_IMGUI
	FETCHCONTENT_SOURCE_DIR_IMGUI
) 

add_library(glfw_wrapper)
target_sources(glfw_wrapper PUBLIC
	FILE_SET glfw_wrapper TYPE CXX_MODULES
	FILES
	./glfw.cpp
)

