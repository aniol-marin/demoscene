set(MODULE_NAME sound)
add_library(${MODULE_NAME})

target_link_libraries(${MODULE_NAME}
	PUBLIC raudio_wrapper
)

target_include_directories( ${MODULE_NAME} PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

target_sources(${MODULE_NAME} PUBLIC
	sound.cpp
)
