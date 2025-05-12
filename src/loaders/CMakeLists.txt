set(MODULE_NAME loaders)

add_library(${MODULE_NAME} INTERFACE
	screen_loader.h
)

target_include_directories( ${MODULE_NAME} INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	$<INSTALL_INTERFACE:loaders>
)

