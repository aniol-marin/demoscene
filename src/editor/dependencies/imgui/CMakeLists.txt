
FetchContent_Declare(
	imgui
	EXCLUDE_FROM_ALL
	GIT_REPOSITORY https://github.com/ocornut/imgui.git
	GIT_TAG 4806a1924ff6181180bf5e4b8b79ab4394118875 # v1.91.9b-docking
)
FetchContent_MakeAvailable(imgui)

add_library(imgui STATIC)
target_sources(imgui PRIVATE
	${imgui_SOURCE_DIR}/imgui.cpp
	${imgui_SOURCE_DIR}/imgui_demo.cpp
	${imgui_SOURCE_DIR}/imgui_draw.cpp
	${imgui_SOURCE_DIR}/imgui_tables.cpp
	${imgui_SOURCE_DIR}/imgui_widgets.cpp
	${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
	${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
	${imgui_SOURCE_DIR}/misc/cpp/imgui_stdlib.cpp
)
target_include_directories(imgui PUBLIC
	$<BUILD_INTERFACE:${imgui_SOURCE_DIR}>
)
target_include_directories(imgui PUBLIC
	$<BUILD_INTERFACE:${imgui_SOURCE_DIR}>/misc/cpp
)
target_include_directories(imgui PUBLIC
	$<BUILD_INTERFACE:${imgui_SOURCE_DIR}/backends>
	$<INSTALL_INTERFACE:imgui>
)
target_link_libraries(imgui
	PRIVATE glfw
	PRIVATE glfw_wrapper
)

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

add_executable(imgui_test)
target_sources(imgui_test PRIVATE
	./imgui_test_main.cpp
)
target_link_libraries(imgui_test
	imgui
	glfw
	glad
)
