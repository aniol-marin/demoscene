
FetchContent_Declare(
	glad
	EXCLUDE_FROM_ALL
	GIT_REPOSITORY https://github.com/Dav1dde/glad.git
	GIT_TAG 73db193f853e2ee079bf3ca8a64aa2eaf6459043 # v2.0.8
	SOURCE_SUBDIR cmake
)
FetchContent_MakeAvailable(glad)

mark_as_advanced(FORCE
	FETCHCONTENT_UPDATES_DISCONNECTED_GLAD
	FETCHCONTENT_SOURCE_DIR_GLAD
) 

# official doc

#project(test C CXX)
# already provided in the project, should be fine
#find_package(glfw3 REQUIRED)

# Path to glad directory
#set(GLAD_SOURCES_DIR "${PROJECT_SOURCE_DIR}/external/glad/")
set(GLAD_SOURCES_DIR /home/bru/demoscene/external/glad-src/)
# Path to glad cmake files
add_subdirectory("${GLAD_SOURCES_DIR}/cmake" glad_cmake)

# Specify glad settings
glad_add_library(glad_gl_core_33 REPRODUCIBLE API gl:core=3.3)

add_executable(multiwin_mx
	#multiwin_mx.cpp
    /home/bru/demoscene/external/glad-src/example/c++/multiwin_mx/multiwin_mx.cpp
    )

# Add glad to your project
target_link_libraries(multiwin_mx
    PUBLIC
        glad_gl_core_33
        glfw
    )
# end official doc

add_library(glad_wrapper)
target_sources(glad_wrapper PUBLIC
	FILE_SET glad_wrapper TYPE CXX_MODULES
	FILES
	./glad.cpp
)

target_link_libraries(glad_wrapper
	PRIVATE glfw_wrapper
	PRIVATE glad
)

