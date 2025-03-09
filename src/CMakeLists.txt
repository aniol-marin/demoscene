add_executable(demoscene)

include(FetchContent)

FetchContent_Declare(
	SDL2
	GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
	GIT_TAG e11183ea6caa3ae4895f4bc54cad2bbb0e365417 # 2.32.2
)
FetchContent_MakeAvailable(SDL2)

FetchContent_Declare(
	raudio
	GIT_REPOSITORY https://github.com/raysan5/raudio.git
	GIT_TAG 711c86eae17db9a94af575f7a5b496244b48b22d # master
)
FetchContent_MakeAvailable(raudio)
target_link_libraries(demoscene
	PRIVATE SDL2
	PRIVATE raudio
)

target_sources(demoscene PRIVATE
	FILE_SET demo TYPE CXX_MODULES
	FILE_SET injection TYPE CXX_MODULES
	FILE_SET definitions TYPE CXX_MODULES
	FILE_SET sdl TYPE CXX_MODULES
	FILE_SET program TYPE CXX_MODULES
	FILE_SET input TYPE CXX_MODULES
	FILE_SET timer TYPE CXX_MODULES
	FILE_SET raudio TYPE CXX_MODULES
	FILE_SET sound TYPE CXX_MODULES
	#FILE_SET effects TYPE CXX_MODULES
	#FILE_SET renderables TYPE CXX_MODULES
	#FILE_SET render TYPE CXX_MODULES
	FILES
	demo.cpp
	injection.cpp
	definitions.cpp
	sdl.cpp
	program.cpp
	input.cpp
	timer.cpp
	raudio.cpp
	sound.cpp
	#renderables.cpp
	#effects.cpp
	#effects/ChessBoard.cpp
	#render.cpp
)

target_sources(demoscene PRIVATE
	main.cpp
	#effects/Effect.cpp
)
