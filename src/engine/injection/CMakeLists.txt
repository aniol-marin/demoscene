set(MODULE_NAME injection)

add_library(${MODULE_NAME} INTERFACE
	injection.h
)

target_include_directories( ${MODULE_NAME} INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

