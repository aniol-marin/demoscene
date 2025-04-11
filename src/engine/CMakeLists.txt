
add_subdirectory(injection)
add_subdirectory(definitions)
add_subdirectory(sdl)
add_subdirectory(input)
add_subdirectory(raudio)

#[[
include(FetchContent)
FetchContent_Declare(
	raudio
	GIT_REPOSITORY https://github.com/raysan5/raudio.git
	GIT_TAG 711c86eae17db9a94af575f7a5b496244b48b22d # master
	SOURCE_SUBDIR projects/CMake
)
FetchContent_MakeAvailable(raudio)

target_link_libraries(demoscene
	PRIVATE raudio
)
]]#

#[[
target_sources( ${ENGINE_LIBRARY_NAME} PUBLIC
	FILE_SET injection TYPE CXX_MODULES
	FILE_SET engine_definitions TYPE CXX_MODULES
	FILE_SET sdl_wrapper TYPE CXX_MODULES
	#FILE_SET program TYPE CXX_MODULES
	#FILE_SET input TYPE CXX_MODULES
	#FILE_SET timer TYPE CXX_MODULES
	#FILE_SET raudio TYPE CXX_MODULES
	#FILE_SET sound TYPE CXX_MODULES
	#FILE_SET effects TYPE CXX_MODULES
	#FILE_SET effect TYPE CXX_MODULES
	#FILE_SET stars TYPE CXX_MODULES
	#FILE_SET renderables TYPE CXX_MODULES
	#FILE_SET render TYPE CXX_MODULES
	#FILE_SET cycle TYPE CXX_MODULES
	#FILE_SET timeline TYPE CXX_MODULES
	FILES
	#demo.cpp
	#program.cpp
	#input.cpp
	#timer.cpp
	#raudio.cpp
	#sound.cpp
	#effects.cpp
	#effects/Effect.cpp
	#effects/Stars.cpp
	#effects/ChessBoard.cpp
	#renderables.cpp
	#render.cpp
	#cycle.cpp
	#timeline.cpp
)
]]#

