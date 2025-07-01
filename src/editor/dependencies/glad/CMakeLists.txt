
FetchContent_Declare(
	glad
	EXCLUDE_FROM_ALL
	GIT_REPOSITORY https://github.com/Dav1dde/glad.git
	GIT_TAG 73db193f853e2ee079bf3ca8a64aa2eaf6459043 # v2.0.8
)
FetchContent_MakeAvailable(glad)

mark_as_advanced(FORCE
	FETCHCONTENT_UPDATES_DISCONNECTED_GLAD
	FETCHCONTENT_SOURCE_DIR_GLAD
) 

add_library(glad_wrapper)
target_sources(glad_wrapper PUBLIC
	#[[ backwards compatibility
	FILE_SET glad_wrapper TYPE CXX_MODULES
	FILES
	]]#
	./glad.cpp
)

