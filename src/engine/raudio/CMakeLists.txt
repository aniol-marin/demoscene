set(MODULE_NAME raudio_wrapper)
add_library(${MODULE_NAME})

include(FetchContent)
FetchContent_Declare(
	raudio
	GIT_REPOSITORY https://github.com/raysan5/raudio.git
	GIT_TAG 711c86eae17db9a94af575f7a5b496244b48b22d # master
	SOURCE_SUBDIR projects/CMake
)
FetchContent_MakeAvailable(raudio)

target_link_libraries( ${MODULE_NAME}
	PRIVATE raudio
	PUBLIC engine_definitions
)

target_sources(${MODULE_NAME} PUBLIC
	FILE_SET raudio_wrapper TYPE CXX_MODULES
	FILES
	raudio.cpp
)
