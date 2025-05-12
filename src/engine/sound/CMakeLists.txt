set(MODULE_NAME sound)

add_library(${MODULE_NAME}
	sound.cpp
)

target_include_directories( ${MODULE_NAME} PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

target_link_libraries(${MODULE_NAME}
	PUBLIC engine_definitions
	PUBLIC raudio_wrapper
)

