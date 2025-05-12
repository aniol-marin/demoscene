set(MODULE_NAME raudio_wrapper)

add_library(${MODULE_NAME}
	raudio.cpp
)

target_include_directories( ${MODULE_NAME} PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

include(FetchContent)
FetchContent_Declare(
	raudio
	EXCLUDE_FROM_ALL
	GIT_REPOSITORY https://github.com/raysan5/raudio.git
	GIT_TAG 711c86eae17db9a94af575f7a5b496244b48b22d # master
	SOURCE_SUBDIR projects/CMake
)
FetchContent_MakeAvailable(raudio)
#[[
FetchContent_Declare(
	sdl-mixer
	GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer.git
	GIT_TAG 171eb2d420d5643e4ee11514a06e04a41a463bbd # 2.8.1
	SOURCE_SUBDIR projects/CMake
)
FetchContent_MakeAvailable(sdl-mixer)
]]#

target_link_libraries( ${MODULE_NAME}
	PUBLIC raudio
	PUBLIC engine_definitions
)
