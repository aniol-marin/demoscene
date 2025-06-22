set(MODULE_NAME raudio_wrapper)
add_library(${MODULE_NAME})

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

target_sources(${MODULE_NAME} PUBLIC
	FILE_SET raudio_wrapper TYPE CXX_MODULES
	FILES
	raudio.cpp
)

mark_as_advanced(FORCE
	BUILD_RAUDIO_EXAMPLES
	FETCHCONTENT_SOURCE_DIR_RAUDIO
	FETCHCONTENT_UPDATES_DISCONNECTED_RAUDIO
	SUPPORT_FILEFORMAT_FLAC
	SUPPORT_FILEFORMAT_MOD
	SUPPORT_FILEFORMAT_MP3
	SUPPORT_FILEFORMAT_OGG
	SUPPORT_FILEFORMAT_QOA
	SUPPORT_FILEFORMAT_WAV
	SUPPORT_FILEFORMAT_XM
	SampleRate_DIR
)

