set(SDL_WRAPPER_LIBRARY_NAME "sdl_wrapper")
add_library(${SDL_WRAPPER_LIBRARY_NAME})

include(FetchContent)

FetchContent_Declare(
	SDL2
	GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
	GIT_TAG e11183ea6caa3ae4895f4bc54cad2bbb0e365417 # 2.32.2
)
FetchContent_MakeAvailable(SDL2)

target_link_libraries(sdl_wrapper
	PRIVATE SDL2
	PRIVATE engine_definitions
)

target_sources(${SDL_WRAPPER_LIBRARY_NAME} PUBLIC
	FILE_SET sdl_wrapper TYPE CXX_MODULES
	FILE_SET engine_definitions TYPE CXX_MODULES
	FILES
	sdl.cpp
)
