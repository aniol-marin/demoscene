set(MODULE_NAME "sdl_wrapper")
add_library(${MODULE_NAME})

include(FetchContent)

FetchContent_Declare(
	SDL2
	GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
	GIT_TAG e11183ea6caa3ae4895f4bc54cad2bbb0e365417 # 2.32.2
)
FetchContent_MakeAvailable(SDL2)

target_link_libraries( ${MODULE_NAME}
	PUBLIC SDL2
	PUBLIC engine_definitions
)

target_include_directories( ${MODULE_NAME} PUBLIC
	"${MODULE_NAME}_SOURCE_DIR"
)

target_sources(${MODULE_NAME} PUBLIC
	sdl.cpp
	PUBLIC FILE_SET HEADERS
	FILES
	sdl.h
)
